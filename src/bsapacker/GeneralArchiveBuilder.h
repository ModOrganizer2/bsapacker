#ifndef GENERALARCHIVEBUILDER_H
#define GENERALARCHIVEBUILDER_H

#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/IArchiveBuilderHelper.h>

namespace BsaPacker
{
	class GeneralArchiveBuilder : public IArchiveBuilder
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IEmitsValueChanged)

	public:
		explicit GeneralArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir& rootDir);
		~GeneralArchiveBuilder() override = default;
		GeneralArchiveBuilder(const GeneralArchiveBuilder&) = delete;
		GeneralArchiveBuilder& operator=(const GeneralArchiveBuilder&) = delete;
		GeneralArchiveBuilder(GeneralArchiveBuilder&&) = delete;
		GeneralArchiveBuilder& operator=(GeneralArchiveBuilder&&) = delete;

		uint32_t setFiles() override;
		void setShareData(bool value) override;
		[[nodiscard]] std::unique_ptr<BSArchiveAuto> getArchive() override;
		[[nodiscard]] uint32_t getFileCount() const override;
		[[nodiscard]] QString getRootPath() const override;

	public Q_SLOTS:
		void cancel() override;

	private:
		const IArchiveBuilderHelper* m_ArchiveBuilderHelper = nullptr;
		std::unique_ptr<BSArchiveAuto> m_Archive;
		bool m_Cancelled;
		QDir m_RootDirectory;
	};
} // namespace BsaPacker

#endif // GENERALARCHIVEBUILDER_H
