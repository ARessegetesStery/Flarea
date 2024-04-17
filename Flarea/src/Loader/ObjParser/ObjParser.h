#pragma 

#include "flrpch.h"

#include "Loader/Parsing.h"

namespace FLR {

    class Entity;

    // parses into the binded entity; erases the original mesh info in it
    class ObjParser
    {
    public:
        ObjParser(Entity* ent, string filename)
        {
            if (ent == nullptr)
            {
#ifdef EQX_DEBUG
                Print("[ERROR] Invalid Entity to parse into!");
                Print("The EntityInfo passed in is:");
                EQX_LOG(ent)
#endif
                ent = nullptr;
                FLR_CORE_ERROR("Trying to parse into nullptr (expecting an `Entity`)");
            }
            this->p_ent = ent;
            this->filename = filename;
        }
        void Parse();

    private:
        Entity* p_ent;
        string filename;
    };

}
