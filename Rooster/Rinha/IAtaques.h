#ifndef ITATECH_JR
#define ITATECH_JR

namespace Rooster {

	class IAtaques {
	public:
		void virtual LightAttack() = 0;
		void virtual HeavyAttack() = 0;
	};
}

#endif