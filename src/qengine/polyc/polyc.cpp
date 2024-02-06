#include "polyc.hpp"

namespace qengine {

	namespace polyc {
		/* have our globals been initialized? */
		bool polyc::initialized = false;

		/*Singleton instance(s) of seeding values*/
		uintptr_t polyc::ciph_x[16]{};

		uintptr_t polyc::ciph_y[16]{};

		uintptr_t polyc::ciph_z[16]{};

		unsigned char polyc::indice_map_x[4]{};

		unsigned char polyc::indice_map_y[8]{};

		unsigned char polyc::indice_map_z[12]{};
	}

}