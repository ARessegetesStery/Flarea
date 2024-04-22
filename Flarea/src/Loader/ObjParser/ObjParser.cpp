#include "flrpch.h"

#include "Geometry/Entity.h"
#include "ObjParser.h"

#pragma warning(push)
#pragma warning(disable:4996)

namespace FLR {

    void ObjParser::Parse()
    {
        if (this->ent == nullptr)
        {
            FLR_CORE_CRITICAL("[ERROR] Invalid Entity to parse into!");
            return;
        }

        /*  Parsing  */
        std::ifstream infile;
        infile.open((filename + ".obj"), std::ios::in);

        ent->ClearMesh();

        if (!infile.is_open())
        {
#ifdef FLR_DEBUG
            FLR_CORE_CRITICAL("[ERROR] Cannot open file \"{0}.obj\"", this->filename);
#endif
            return;
        }
        
        char linebuf[1024];
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;
        std::vector<Parsing::face> fs;
        char curObjName[128];
        glm::vec3 v3;
        glm::vec2 v2;
        v.push_back(v3);
        vt.push_back(v2);
        vn.push_back(v3);
        bool isFirstObj = true;

        while (infile.getline(linebuf, 1024, '\n'))
        {
            if (linebuf[0] == '#')
                continue;
            else if (linebuf[0] == 'o' && linebuf[1] == ' ')
            {
                if (isFirstObj == false)
                {
                    FLR_CORE_CRITICAL("[ERROR] Parsing .obj files containing multiple objects is not supported for now");
                }
                else
                {
                    isFirstObj = false;
                }

                if (std::sscanf(linebuf, "o %s", curObjName))
                {
                    if (curObjName[0] > 64 && curObjName[0] < 91)
                    {
                        curObjName[0] = curObjName[0] + 32;
                    }
                    for (int i = 0; i < strlen(curObjName); ++i)
                    {
                        char c = curObjName[i];
                        if (c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
                        {
                            curObjName[i] = '_';
                        }
                    }
                }
            }
            else if (linebuf[0] == 'v' && linebuf[1] == ' ')
            {
                if (std::sscanf(linebuf, "v %f %f %f", &v3.x, &v3.y, &v3.z))
                    v.push_back(v3);
            }
            else if (linebuf[0] == 'v' && linebuf[1] == 't')
            {
                if (std::sscanf(linebuf, "vt %f %f", &v2.x, &v2.y))
                    vt.push_back(v2);
            }
            else if (linebuf[0] == 'v' && linebuf[1] == 'n')
            {
                if (std::sscanf(linebuf, "vn %f %f %f", &v3.x, &v3.y, &v3.z))
                    vn.push_back(v3);
            }
            else if (linebuf[0] == 'f' && linebuf[1] == ' ')
            {
                Parsing::face F;
                if (std::sscanf(linebuf, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
                    &F.f[0].x, &F.f[0].y, &F.f[0].z,
                    &F.f[1].x, &F.f[1].y, &F.f[1].z,
                    &F.f[2].x, &F.f[2].y, &F.f[2].z,
                    &F.f[3].x, &F.f[3].y, &F.f[3].z))
                    fs.push_back(F);
            }
        }

        // writing to mesh
        for (auto iter = fs.begin(); iter != fs.cend(); ++iter)
        {
            ent->AddFaceToMesh(Vertex(v[iter->f[0].x], vn[iter->f[0].z], vt[iter->f[0].y]),
                Vertex(v[iter->f[1].x], vn[iter->f[1].z], vt[iter->f[1].y]), 
                Vertex(v[iter->f[2].x], vn[iter->f[2].z], vt[iter->f[2].y]));
            ent->AddFaceToMesh(Vertex(v[iter->f[2].x], vn[iter->f[2].z], vt[iter->f[2].y]),
                Vertex(v[iter->f[0].x], vn[iter->f[0].z], vt[iter->f[0].y]),
                Vertex(v[iter->f[3].x], vn[iter->f[3].z], vt[iter->f[3].y]));
        }

        FLR_CORE_INFO("Finished parsing {0}", filename);

        infile.close();
    }

}

#pragma warning(pop)
