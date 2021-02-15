#pragma once

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

namespace OmniliumKnox {
	namespace Core {
		class CORE_API Core {
		public:
			Core(void);
		};
	}
};
