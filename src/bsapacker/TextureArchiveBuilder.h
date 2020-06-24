#ifndef TEXTUREARCHIVEBUILDER_H
#define TEXTUREARCHIVEBUILDER_H

#include <bsapacker/IArchiveBuilder.h>
#include <bsapacker/IArchiveBuilderHelper.h>

namespace BsaPacker
{
	class TextureArchiveBuilder : public IArchiveBuilder
	{
		Q_OBJECT
			Q_INTERFACES(BsaPacker::IEmitsValueChanged)

	public:
		explicit TextureArchiveBuilder(const IArchiveBuilderHelper* archiveBuilderHelper, const QDir&);
		~TextureArchiveBuilder() override = default;

		uint32_t setFiles() override;
		void setShareData(bool) override;
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

		static void DDSCallback(bsa_archive_t archive, const wchar_t* file_path, bsa_dds_info_t* dds_info, void* context);
	};
} // namespace BsaPacker

#endif // TEXTUREARCHIVEBUILDER_H
