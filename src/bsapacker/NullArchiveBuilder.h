#ifndef NULLARCHIVEBUILDER_H
#define NULLARCHIVEBUILDER_H

#include <bsapacker/IArchiveBuilder.h>

namespace BsaPacker
{
	class NullArchiveBuilder : public IArchiveBuilder
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IEmitsValueChanged)

	public:
		NullArchiveBuilder() = default;
		~NullArchiveBuilder() override = default;

		uint32_t setFiles() override;
		void setShareData(bool) override;
		[[nodiscard]] std::unique_ptr<BSArchiveAuto> getArchive() override;
		[[nodiscard]] uint32_t getFileCount() const override;
		[[nodiscard]] QString getRootPath() const override;

	public Q_SLOTS:
		void cancel() override;
	};
} // namespace BsaPacker

#endif // NULLARCHIVEBUILDER_H
