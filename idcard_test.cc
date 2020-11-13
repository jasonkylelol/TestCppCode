#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sstream>

int32_t idcardMask(char* id_card_data)
{
    std::string id_card(id_card_data);
    if (id_card == "")
    {
        return 0;
    }
    time_t cur_time = time(nullptr);
    struct tm tm_buf;
    if (nullptr == localtime_r(&cur_time, &tm_buf))
    {
        printf("gmtime_r failed!\n");
        return -1;
    }
    // 用strftime
    char str_buf[32];
    if (0 == std::strftime(str_buf, sizeof(str_buf), "%Y%m%d", &tm_buf))
    {
        printf("strftime failed!\n");
        return -1;
    }
    uint32_t cur_date = 0;
    try
    {
        cur_date = std::stoi(str_buf);
    }
    catch (const std::exception& e)
    {
        printf("stoi catch an exception: %s str_buf:%s\n", e.what(), str_buf);
        return -1;
    }
    uint32_t age_date = 0;
    if (id_card.size() == 15)
    {
        // 15位身份证号 取 7到12位为出生年月日 格式为 xxxxxx 默认是19xxxxxx
        try
        {
            age_date = (19 * 1000000) + std::stoi(id_card.substr(6, 6));
        }
        catch (const std::exception& e)
        {
            printf("parse age_date catch an exception: %s id_card: %s\n",
                e.what(), id_card.data());
            return -1;
        }
    }
    else if (id_card.size() == 18)
    {
        // 取18位身份证出生日期
        try
        {
            age_date = std::stoi(id_card.substr(6, 8));
        }
        catch (const std::exception& e)
        {
            printf("parse age_date catch an exception: %s id_card:%s\n",
                e.what(), id_card.data());
            return -1;
        }
    }
    else
    {
        printf("invalid id_card length! id_card:%s\n", id_card.data());
        return -1;
    }
    // 提取用户年龄
    uint32_t age = 0;
    uint32_t cur_year = cur_date / 10000;
    uint32_t cur_monday = cur_date % 10000;
    uint32_t age_year = age_date / 10000;
    uint32_t age_monday = age_date % 10000;
    if (cur_monday > age_monday)
    {
        age = cur_year - age_year;
    }
    else
    {
        age = cur_year - age_year -1;
    }
    std::ostringstream oss;
    oss << "cur_date:" << cur_date << " cur_year:" << cur_year << " cur_monday:" << cur_monday
        << " age_date:" << age_date << " age_year:" << age_year << " age_monday:" << age_monday
        << " age:" << age;
    printf("%s\n", oss.str().data());
    printf("id_card: %s\n", id_card.data());
    if (id_card.size() == 18)
    {
        // 身份证号的第 2 -  11位以*隐藏
        id_card.replace(1, 10, "**********");
        printf("new id_card:%s\n", id_card.data());
    }
    else if (id_card.size() == 15)
    {
        // 身份证号的第 2 -  11位以*隐藏
        id_card.replace(1, 10, "**********");
        printf("new id_card:%s\n", id_card.data());
    }
    return 0;
}

int main() {
    idcardMask("12345619901112310X");
    idcardMask("350424870506202");
    return 0;
}
