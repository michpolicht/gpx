#ifndef IRECORDABLE_HPP
#define IRECORDABLE_HPP

#include <cstddef>

namespace gpx {
namespace phy {

class IRecordable
{
	public:
		virtual std::size_t snapshotSize() const = 0;

		virtual void store(char * snapshot) const = 0;

		virtual void restore(char * snapshot) = 0;

	protected:
		~IRecordable() {}
};

}
}

#endif // IRECORDABLE_HPP
