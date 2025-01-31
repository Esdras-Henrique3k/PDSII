#ifndef TXT_TO_EXCEL_EXPORTER_HPP
#define TXT_TO_EXCEL_EXPORTER_HPP

#include <string>

class TxtToExcelExporter {
public:
    static void exportToCsv(const std::string& userName, const std::string& outputDir);
};

#endif // TXT_TO_EXCEL_EXPORTER_HPP
