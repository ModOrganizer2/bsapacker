#ifndef IOVERRIDEFILESERVICE_H
#define IOVERRIDEFILESERVICE_H

#include <QString>

namespace BsaPacker {
	class IOverrideFileService {
	public:
		virtual ~IOverrideFileService() = default;
		virtual bool CreateOverrideFile(const int nexusId,
			const QString& modPath,
			const QString& archiveNameBase) const = 0;
	};
} // namespace BsaPacker

#endif // IOVERRIDEFILESERVICE_H