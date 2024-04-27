#ifndef RELEASE_H
#define RELEASE_H
namespace utils {
	template <typename callable>
	class release {
	private:
		callable exit_function;
		bool execute_on_destruction; // exposition only

	public:
		// construction
		explicit
			release(callable&& f) :
			exit_function(std::move(f))
			, execute_on_destruction(true)
		{
		}

		// destruction
		~release() {
			if (execute_on_destruction)
				this->exit_function();
		}

		release(release const&) = delete;
		release(release const&&) = delete;
		void operator=(release const&) = delete;
		release& operator=(release&&) = delete;
	};
}
#endif // RELEASE_H