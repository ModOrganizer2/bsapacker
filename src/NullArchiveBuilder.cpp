#include <bsapacker/NullArchiveBuilder.h>

namespace BsaPacker
{
	uint32_t NullArchiveBuilder::setFiles()
	{
		return 0;
	}

	void NullArchiveBuilder::setShareData(const bool)
	{
	}

	std::unique_ptr<BSArchiveAuto> NullArchiveBuilder::getArchive()
	{
		return nullptr;
	}

	uint32_t NullArchiveBuilder::getFileCount() const
	{
		return 0;
	}

	QString NullArchiveBuilder::getRootPath() const
	{
		return QString();
	}

	void NullArchiveBuilder::cancel()
	{
	}
} // namespace BsaPacker
