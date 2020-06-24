#ifndef FILEWRITERSERVICE_H
#define FILEWRITERSERVICE_H

#include <bsapacker/IFileWriterService.h>

namespace BsaPacker
{
	class FileWriterService : public IFileWriterService
	{
	public:
		FileWriterService() = default;
		~FileWriterService() override = default;
		bool Write(const std::string& path, const char* payload, const uint32_t size) const override;
	};
}
#endif // FILEWRITERSERVICE_H
