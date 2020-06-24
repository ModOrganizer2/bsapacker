#ifndef IARCHIVEBUILDER_H
#define IARCHIVEBUILDER_H

#include <bsapacker/IEmitsValueChanged.h>
#include <qlibbsarch/BSArchiveAuto.h>

namespace BsaPacker
{
	class IArchiveBuilder : public IEmitsValueChanged
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IEmitsValueChanged)

	public:
		virtual ~IArchiveBuilder() = default;
		virtual uint32_t setFiles() = 0;
		virtual void setShareData(bool) = 0;
		[[nodiscard]] virtual std::unique_ptr<BSArchiveAuto> getArchive() = 0;
		[[nodiscard]] virtual uint32_t getFileCount() const = 0;
		[[nodiscard]] virtual QString getRootPath() const = 0;
	};
}  // namespace BsaPacker

#endif // IARCHIVEBUILDER_H
