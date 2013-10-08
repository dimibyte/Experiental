

#include "engine.h"
#include "game/example.h"

class CHighScoresTable : public Singleton<CHighScoresTable>
{
public:
    CHighScoresTable();
    virtual ~CHighScoresTable();

    void serialize(ISerializer *s);

    bool load();
    bool save();

    struct hs
    {
        std::string name;
        unsigned long score;
    } scores[10];

    inline int getScoreCount() const { return 10; };
};

CHighScoresTable::CHighScoresTable()
{
    for(int i = 0; i < 10; i++)
    {
        scores[i].name = "Nobody";
        scores[i].score = 100 - i * 10;
    }
}

CHighScoresTable::~CHighScoresTable()
{
}

void CHighScoresTable::serialize(ISerializer *s)
{
    for(int i = 0; i < 10; i++)
    {
        s->IO(scores[i].name);
        s->IO(scores[i].score);
    }
}

bool CHighScoresTable::load()
{
    unsigned long size = 0;

    FILE *fp = fopen("highscor.dat", "rb");
    if(!fp)
        return false;

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *buffer = new unsigned char[size];
    if(fread(buffer, 1, size, fp) != size)
    {
        fclose(fp);
        delete[] buffer;
        return false;
    }
    fclose(fp);

    CSerialLoader sl(buffer, size);
    serialize(&sl);
    assert(sl.getFlow() == 0);

    delete[] buffer;

    return true;
}

//And here's the complimetary save function.
//Again, it opens the file; it uses both a CSerialSizer *and* a CSerialSaver to get the size of the data to write out,
//though in fact this could be made more efficient by writing a CFileSaver which writes directly to the file rather than to a buffer.
//The same goes for the load function.
bool CHighScoresTable::save()
{
    FILE *fp = fopen("highscor.dat", "wb");
    if(!fp)
        return false;

    CSerialSizer ss;
    serialize(&ss);
    unsigned long size = ss.getLength();

    unsigned char *buffer = new unsigned char[size];
    CSerialSaver sv(buffer, size);
    serialize(&sv);
    assert(sv.getFlow() == 0);

    fwrite(buffer, size, 1, fp);
    fclose(fp);
    delete[] buffer;

    return true;
}
