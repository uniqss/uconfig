class IntString
{
public:
    uint32 KeyInt;
    string KeyString;
};




// 数据结构
class DT_Hero_Config
{
public:
    // 字段类型 字段名
	uint32 Id;
	uint32 Type;
	string Name;
	string Desc;
};

// 加载函数
void DT_Hero_Config_LoadData(DT_Hero_Config* pConfig, DataLine* pData)
{
}

class CfgDT_Hero_Config_Data
{
public:
    vector<DT_Hero_Config> Datas;
    map<uint32, DT_Hero_Config*> DT_Hero_ConfigItems;
    map<IntString, DT_Hero_Config*> DT_Hero_ConfigItems2;
};
