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
#ifdef FLR_DEBUG
                FLR_CORE_ERROR("[ERROR] Invalid Entity to parse into!");
                FLR_CORE_ERROR("Trying to parse into nullptr (expecting an `Entity`)");
#endif
            }
            this->ent = ent;
            this->filename = filename;
        }
        void Parse();

    private:
        Entity* ent;
        string filename;
    };

}
