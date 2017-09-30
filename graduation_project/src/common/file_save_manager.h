
#include <vector>
#include <string>

#include "singleton.h"

typedef std::vector<double> LineData;

struct FileObject
{
    std::string file_name;
    std::vector<LineData> file_data;
};

class FileSaveManager:public Singleton<FileSaveManager>
{
public:
    FileSaveManager() {};
    ~FileSaveManager() {};
	int AddFile(const std::string &file_name,std::vector<LineData> &file_data);
	int SaveFile() const;
private:
    std::vector<FileObject> file_object_vec_; 
};
