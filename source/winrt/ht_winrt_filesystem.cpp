
#include <ht_winrt_filesystem.h>
#include <ht_string.h>
#include <ht_os.h>

namespace Hatchit
{
    namespace Core
    {
        namespace WinRT
        {
            std::string Directory::LocalFolder()
            {
                if (Windows::Storage::ApplicationData::Current->LocalFolder)
                {
                    Platform::String^ localfolder = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
                
                    return wstring_to_string(localfolder->Data()) + "\\";
                }

                return "";
            }
            std::string Directory::LocalCacheFolder()
            {
                Platform::String^ localCacheFolder = Windows::Storage::ApplicationData::Current->LocalCacheFolder->Path;

                return wstring_to_string(localCacheFolder->Data()) + "\\";
            }
            std::string Directory::RoamingFolder()
            {
                Platform::String^ roamingFolder = Windows::Storage::ApplicationData::Current->RoamingFolder->Path;

                return wstring_to_string(roamingFolder->Data()) + "\\";
            }
            std::string Directory::SharedLocalFolder()
            {
                if(Windows::Storage::ApplicationData::Current->SharedLocalFolder)
                {
                    Platform::String^ sharedLocalFolder = Windows::Storage::ApplicationData::Current->SharedLocalFolder->Path;

                    return wstring_to_string(sharedLocalFolder->Data()) + "\\";
                }
                
                return "";
            }
            std::string Directory::TemporaryFolder()
            {
                Platform::String^ temporaryFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder->Path;

                return wstring_to_string(temporaryFolder->Data()) + "\\";
            }
        }
    }
}