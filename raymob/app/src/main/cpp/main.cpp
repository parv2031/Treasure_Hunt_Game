
#include "raymob.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <random>

using namespace std;
int coins = 25, diamonds = 0 ,level=0;
int treasures = 0, penalty = 0;
string clue_giver(vector<string>& clues);
//list of buildings
vector<string> name={"LHC","SPORTS COMPLEX","MESS","LABORATORY","PHC","AIDS SCHOOL","SCHOOL OF LIBERAL ARTS","TEMPLE","FACULTY QUARTERS","RESTAURANT","LIBRARY"};

vector<vector<string>> identities = {
        {
                "Minds wander, but bodies stay seated here.",
                "My walls have heard every subject, but never taken a test.",
                "I host silent listeners and loud speakers, yet I am neither library nor stadium.",
                "Rows and rows, but not a cinema show.",
                "Where slides change, but the subject remains.",
                "Yahan har din naya chehra, magar manzil wahi purani.",
                "Yahan bolne walon ki qatar nahin, sunne walon ki bheed hai.",
                "Yahan har kursi ki apni kahani hai, par koi sunta nahin.",
                "Ghari to nahi, par har nazar waqt par tikti hai.",
                "Yahan har vishay ki chhaya hai, par koi kitaab nahin."
        },
        {
                "Yahan paseena bahta hai, par kitaaben nahin khulti.",
                "Jahan joote badalte hain, par jazba wahi rehta hai.",
                "Yahan haar-jeet roz badalti hai, par jazba hamesha rehta hai.",
                "Yahan seeti ki awaaz padhai ki ghanti se tez hai.",
                "Yahan shor bhi hai, taaliyaan bhi, par padhai nahin.",
                "Where stamina speaks louder than words ever could.",
                "I'm the heart tha t pumps adrenaline, not blood.",
                "Here seasons change with tournaments, not weather.",
                "Where the only homework is training harder tomorrow.",
                "I shelter dreams awake on the field, not in sleep."
        },
        {
                "Where hunger meets its match, but no games are played.",
                "I serve hundreds but never get tired of the same menu.",
                "Here timing is everything, yet no watches are worn.",
                "Where plates are plenty but patience runs thin.",
                "I echo with complaints, yet everyone returns tomorrow.",
                "Yahan sab line mein khade hote hain, par train nahin aati.",
                "Yahan roz nayi recipe ka intezaar, par menu wahi purana.",
                "Yahan pet bharta hai, par dil kabhi nahin bharta.",
                "Yahan sabse zyada noise, par koi music nahin.",
                "Yahan timetable sabko pata hai, par padhai ka nahin."
        },
        {
                "Where molecules mingle but no party is thrown.",
                "I echo with drops and sparks, yet no concert hall I am.",
                "Here microscopes and voltmeters share the same shelf.",
                "I smell of acids and solvents, but not a single perfume.",
                "Where theory meets glassware under one roof.",
                "Yahan pipette ki boonden girti hain, par khamoshi tutti nahin.",
                "Yahan Bunsen burner ki aag jalti hai, par jalti nahin zindagi.",
                "Yahan cells bhi dekhe jaate hain, aur circuits bhi sajte hain.",
                "Yahan slides badalte hain, par syllabus wahi rehta hai.",
                "Yahan voltage bhi napte hain, aur volume bhi mapte hain."
        },
        {
                "Where healing hands meet hopeful hearts every day.",
                "I dispense care, not prescriptions for patience.",
                "Here vitals speak louder than words ever could.",
                "I shelter both stethoscopes and smiles under one roof.",
                "Where queues form for cures, not for classrooms.",
                "Yahan dawa nahin, par dawaai ki umeed milti hai.",
                "Yahan doctor ki ghanti bajti hai, par pathshala nahin hoti.",
                "Yahan har dard ki kahani milti hai, par syllabus nahin.",
                "Yahan clinic ki khidki khulti hai, par khushiyon ki bhi.",
                "Yahan zakhm bharte hain, par dino ke naam nahin."
        },
        {
                "Where algorithms learn while students teach each other.",
                "I speak in codes but solve real-world puzzles.",
                "Here data whispers secrets louder than lectures.",
                "I forge minds that build minds from zeros and ones.",
                "Where models train harder than athletes ever could.",
                "Yahan data ki baarish hoti hai, par bheegna mana hai.",
                "Yahan neurons jagte hain, par khwabe software ke hote hain.",
                "Yahan har query ka jawab machine bhi de sakti hai.",
                "Yahan code likha jaata hai, par baatein insights ki hoti hain.",
                "Yahan statistics ginte hain, par kahaniyan khud bolti hain."
        },
        {
                "Where every question sparks a thousand perspectives.",
                "I house voices from past and future under one roof.",
                "Here words wield power greater than any sword.",
                "I am a crossroads of cultures, ideas, and debates.",
                "Where minds unshackle themselves from narrow paths.",
                "Yahan har kalam kahaniyan bun-ta hai, par silai nahin hoti.",
                "Yahan dhadkan mehsoos hoti hai, magar kadar nahin.",
                "Yahan soch ki udaan hai, par pankh nahin.",
                "Yahan har lafz mein gehraayi hai, par awaaz halki hai.",
                "Yahan kitabein khulti hain, par dil ki kitaab nahin."
        },
        {
                "Where incense rises, and worries find their rest.",
                "I host silent prayers louder than any lecture's applause.",
                "Here faith convenes without assignments or grades.",
                "I stand among stones, but shelter souls, not lectures.",
                "Where bells ring louder than campus crowds any day.",
                "Yahan ghanti ki dhun goonjti hai, par syllabus nahin.",
                "Yahan prarthana ki goonj hoti hai, par exams nahin.",
                "Yahan mantron ki awaaz hai, par coding nahin.",
                "Yahan kadam rukte hain, par vishayon ka pata nahin.",
                "Yahan shanti milti hai, par shiksha nahin."
        },
        {
                "Where teaching minds unwind with family laughter at dusk.",
                "I house scholars and their kin beneath one roof of comfort.",
                "Here lessons end for the day, but dinner discussions begin.",
                "I stand between classrooms and playgrounds, silent witness to both.",
                "Where office hours cease, and home hours prevail.",
                "Yahan siyahi ki jagah bachon ke geet goonjte hain.",
                "Yahan syllabus badalta hai ghar ke routine mein.",
                "Yahan professors khud ek parivaar ban jaate hain.",
                "Yahan lectures nahin, par family meetings roz hoti hain.",
                "Yahan aangan hi sabse bada playground ban jaata hai."
        },
        {
                "Where flavors meet like old friends, but no speeches are given.",
                "I offer courses of the edible kind, not the academic.",
                "Here hunger submits, and palates rejoice.",
                "I am a tent for taste, not a hall for history.",
                "You'll savor every session, but no grades await.",
                "Yahan swaad ki mehfil hai, par padhai ki ghanti nahin bajti.",
                "Yahan kursiyan bhari hoti hain, par pen ki zaroorat nahin.",
                "Yahan bhook mitti hai, par koi grade nahin milta.",
                "Yahan mehmaan aate hain, par attendance nahin li jaati.",
                "Yahan khamoshi zyada hai, par zayka khud bol uthta hai."
        },
        {
                "Where silence speaks louder than any lecture's applause.",
                "I house worlds in pages, yet never travel a mile.",
                "Here knowledge rests on shelves, but minds roam free.",
                "I welcome every question, yet never raise my voice.",
                "Where time slows down, but stories speed up.",
                "Yahan har kitab apni dastaan batati hai, par khamoshi nahin toot-ti.",
                "Yahan lamhe beette hain, par syllabus nahin bhoolta.",
                "Yahan har panne mein rahasya hai, par koi chaukanna nahin hota.",
                "Yahan naqsh-e-qadam kam, par jahaan-bhari soch zyada hai.",
                "Yahan har alfaaz ke saath imtihaan nahin, par khayal zaroor nikharta hai."
        }
};

string clue_giver(int bid) {
    random_device rd;
    mt19937 gen(rd());

    // Collect indices of rows except the 'bid' row
    vector<int> valid_rows;
    for (int i = 0; i < identities.size(); ++i) {
        if (i != bid && !identities[i].empty()) {
            valid_rows.push_back(i);
        }
    }

    if (valid_rows.empty()) {
        return ""; // No valid row to choose from
    }

    // Pick a random row index (excluding 'bid')
    uniform_int_distribution<> row_dist(0, valid_rows.size() - 1);
    int chosen_row = valid_rows[row_dist(gen)];

    // Pick a random element from the chosen row
    uniform_int_distribution<> elem_dist(0, identities[chosen_row].size() - 1);
    int chosen_elem = elem_dist(gen);

    return identities[chosen_row][chosen_elem];
}

// Global game state variables
static float playerX, playerY;
static string playerClue=clue_giver(-1);
static Camera2D camera;
static float joystickRadius, joystickBaseRadius;
static Vector2 joystickCenter;
static bool joystickActive = false;
static Vector2 joystickDirection = { 0, 0 };
static bool see=false,still=false,nitro=false,nitroOn=false;
int pbid=INT_MIN;
static Vector2 prevTouch1 = {0,0}, prevTouch2 = {0,0};
static float prevPinchDist = 0.0f;
static bool wasPanning = false, wasPinching = false,st=false;

// identity checker and and clue giver function
bool identity_checker(string& s, vector<string>& identities){
    if(find(identities.begin(),identities.end(),s)==identities.end()) return false;
    else return true;
}

struct pair_hash {
    size_t operator()(const std::pair<int, int>& p) const {
        size_t seed = 0;
        seed ^= std::hash<int>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= std::hash<int>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

// Usage
std::unordered_map<std::pair<int,int>, int, pair_hash> tileMap = {{ { 6, 45 }, 8 },{ { 7, 45 }, -1 },{ { 7, 101 }, 6 },{ { 8, 0 }, -1 },{ { 8, 1 }, -1 },{ { 8, 2 }, -1 },{ { 8, 3 }, -1 },{ { 8, 4 }, -1 },{ { 8, 5 }, -1 },{ { 8, 6 }, -1 },{ { 8, 7 }, -1 },{ { 8, 8 }, -1 },{ { 8, 9 }, -1 },{ { 8, 10 }, -1 },{ { 8, 11 }, -1 },{ { 8, 12 }, -1 },{ { 8, 13 }, -1 },{ { 8, 14 }, -1 },{ { 8, 15 }, -1 },{ { 8, 16 }, -2 },{ { 8, 17 }, -1 },{ { 8, 18 }, -1 },{ { 8, 19 }, -1 },{ { 8, 20 }, -1 },{ { 8, 21 }, -1 },{ { 8, 22 }, -1 },{ { 8, 23 }, -1 },{ { 8, 24 }, -1 },{ { 8, 25 }, -1 },{ { 8, 26 }, -1 },{ { 8, 27 }, -1 },{ { 8, 28 }, -1 },{ { 8, 29 }, -1 },{ { 8, 30 }, -1 },{ { 8, 31 }, -1 },{ { 8, 32 }, -1 },{ { 8, 33 }, -1 },{ { 8, 34 }, -1 },{ { 8, 35 }, -1 },{ { 8, 36 }, -1 },{ { 8, 37 }, -1 },{ { 8, 38 }, -1 },{ { 8, 39 }, -1 },{ { 8, 40 }, -1 },{ { 8, 41 }, -1 },{ { 8, 42 }, -1 },{ { 8, 43 }, -1 },{ { 8, 44 }, -1 },{ { 8, 45 }, -1 },{ { 8, 46 }, -1 },{ { 8, 47 }, -1 },{ { 8, 48 }, -1 },{ { 8, 49 }, -1 },{ { 8, 50 }, -1 },{ { 8, 51 }, -1 },{ { 8, 52 }, -1 },{ { 8, 53 }, -1 },{ { 8, 54 }, -1 },{ { 8, 55 }, -1 },{ { 8, 56 }, -1 },{ { 8, 57 }, -1 },{ { 8, 58 }, -1 },{ { 8, 59 }, -1 },{ { 8, 60 }, -1 },{ { 8, 61 }, -1 },{ { 8, 62 }, -1 },{ { 8, 63 }, -2 },{ { 8, 64 }, -1 },{ { 8, 65 }, -1 },{ { 8, 66 }, -1 },{ { 8, 67 }, -1 },{ { 8, 68 }, -1 },{ { 8, 69 }, -1 },{ { 8, 70 }, -1 },{ { 8, 71 }, -1 },{ { 8, 72 }, -1 },{ { 8, 73 }, -1 },{ { 8, 74 }, -1 },{ { 8, 75 }, -1 },{ { 8, 76 }, -1 },{ { 8, 77 }, -1 },{ { 8, 78 }, -1 },{ { 8, 79 }, -1 },{ { 8, 80 }, -1 },{ { 8, 81 }, -1 },{ { 8, 82 }, -1 },{ { 8, 83 }, -1 },{ { 8, 84 }, -1 },{ { 8, 85 }, -1 },{ { 8, 86 }, -1 },{ { 8, 87 }, -1 },{ { 8, 88 }, -1 },{ { 8, 89 }, -1 },{ { 8, 90 }, -1 },{ { 8, 91 }, -1 },{ { 8, 92 }, -1 },{ { 8, 93 }, -1 },{ { 8, 94 }, -1 },{ { 8, 95 }, -1 },{ { 8, 96 }, -1 },{ { 8, 97 }, -1 },{ { 8, 98 }, -1 },{ { 8, 99 }, -1 },{ { 8, 100 }, -1 },{ { 8, 101 }, -1 },{ { 8, 102 }, -1 },{ { 8, 103 }, -1 },{ { 8, 104 }, -1 },{ { 8, 105 }, -1 },{ { 8, 106 }, -1 },{ { 8, 107 }, -1 },{ { 8, 108 }, -1 },{ { 8, 109 }, -1 },{ { 8, 110 }, -1 },{ { 8, 111 }, -1 },{ { 8, 112 }, -1 },{ { 8, 113 }, -1 },{ { 8, 114 }, -1 },{ { 8, 115 }, -1 },{ { 8, 116 }, -1 },{ { 8, 117 }, -1 },{ { 8, 118 }, -1 },{ { 8, 119 }, -1 },{ { 8, 120 }, -1 },{ { 8, 121 }, -1 },{ { 8, 122 }, -1 },{ { 8, 123 }, -1 },{ { 8, 124 }, -1 },{ { 8, 125 }, -1 },{ { 8, 126 }, -1 },{ { 8, 127 }, -1 },{ { 8, 128 }, -2 },{ { 9, 16 }, -1 },{ { 9, 63 }, -1 },{ { 9, 108 }, -1 },{ { 9, 128 }, -1 },{ { 10, 16 }, -1 },{ { 10, 63 }, -1 },{ { 10, 108 }, -1 },{ { 10, 128 }, -1 },{ { 11, 16 }, -1 },{ { 11, 63 }, -1 },{ { 11, 108 }, -1 },{ { 11, 128 }, -1 },{ { 12, 16 }, -1 },{ { 12, 63 }, -1 },{ { 12, 108 }, 9 },{ { 12, 128 }, -1 },{ { 13, 16 }, -1 },{ { 13, 63 }, -1 },{ { 13, 128 }, -1 },{ { 14, 16 }, -1 },{ { 14, 63 }, -1 },{ { 14, 128 }, -1 },{ { 14, 137 }, 4 },{ { 15, 16 }, -1 },{ { 15, 63 }, -1 },{ { 15, 128 }, -1 },{ { 15, 137 }, -1 },{ { 16, 16 }, -1 },{ { 16, 63 }, -1 },{ { 16, 128 }, -1 },{ { 16, 137 }, -1 },{ { 17, 16 }, -1 },{ { 17, 63 }, -1 },{ { 17, 128 }, -1 },{ { 17, 137 }, -1 },{ { 18, 16 }, -1 },{ { 18, 63 }, -1 },{ { 18, 128 }, -1 },{ { 18, 137 }, -1 },{ { 19, 16 }, -1 },{ { 19, 63 }, -1 },{ { 19, 115 }, 9 },{ { 19, 116 }, -1 },{ { 19, 117 }, -1 },{ { 19, 118 }, -1 },{ { 19, 119 }, -1 },{ { 19, 120 }, -1 },{ { 19, 121 }, -1 },{ { 19, 122 }, -1 },{ { 19, 123 }, -1 },{ { 19, 124 }, -1 },{ { 19, 125 }, -1 },{ { 19, 126 }, -1 },{ { 19, 127 }, -1 },{ { 19, 128 }, -1 },{ { 19, 129 }, -1 },{ { 19, 130 }, -1 },{ { 19, 131 }, -1 },{ { 19, 132 }, -1 },{ { 19, 133 }, -1 },{ { 19, 134 }, -1 },{ { 19, 135 }, -1 },{ { 19, 136 }, -1 },{ { 19, 137 }, -1 },{ { 20, 16 }, -1 },{ { 20, 63 }, -1 },{ { 20, 128 }, -1 },{ { 21, 16 }, -1 },{ { 21, 63 }, -1 },{ { 21, 128 }, -1 },{ { 22, 16 }, -1 },{ { 22, 63 }, -1 },{ { 22, 128 }, -1 },{ { 23, 16 }, -1 },{ { 23, 63 }, -1 },{ { 23, 128 }, -1 },{ { 24, 16 }, -1 },{ { 24, 63 }, -1 },{ { 24, 128 }, -1 },{ { 25, 16 }, -1 },{ { 25, 37 }, 0 },{ { 25, 63 }, -1 },{ { 25, 108 }, 9 },{ { 25, 128 }, -1 },{ { 26, 16 }, -1 },{ { 26, 37 }, -1 },{ { 26, 63 }, -1 },{ { 26, 108 }, -1 },{ { 26, 128 }, -1 },{ { 27, 16 }, -1 },{ { 27, 37 }, -1 },{ { 27, 63 }, -1 },{ { 27, 108 }, -1 },{ { 27, 128 }, -1 },{ { 28, 16 }, -1 },{ { 28, 37 }, -1 },{ { 28, 63 }, -1 },{ { 28, 80 }, 3 },{ { 28, 108 }, -1 },{ { 28, 128 }, -1 },{ { 29, 16 }, -2 },{ { 29, 17 }, -1 },{ { 29, 18 }, -1 },{ { 29, 19 }, -1 },{ { 29, 20 }, -1 },{ { 29, 21 }, -1 },{ { 29, 22 }, -1 },{ { 29, 23 }, -1 },{ { 29, 24 }, -1 },{ { 29, 25 }, -1 },{ { 29, 26 }, -1 },{ { 29, 27 }, -1 },{ { 29, 28 }, -1 },{ { 29, 29 }, -1 },{ { 29, 30 }, -1 },{ { 29, 31 }, -1 },{ { 29, 32 }, -1 },{ { 29, 33 }, -1 },{ { 29, 34 }, -1 },{ { 29, 35 }, -1 },{ { 29, 36 }, -1 },{ { 29, 37 }, -1 },{ { 29, 38 }, -1 },{ { 29, 39 }, -1 },{ { 29, 40 }, -1 },{ { 29, 41 }, -1 },{ { 29, 42 }, -1 },{ { 29, 43 }, -1 },{ { 29, 44 }, -1 },{ { 29, 45 }, -1 },{ { 29, 46 }, -1 },{ { 29, 47 }, -1 },{ { 29, 48 }, -1 },{ { 29, 49 }, -1 },{ { 29, 50 }, -1 },{ { 29, 51 }, -1 },{ { 29, 52 }, -1 },{ { 29, 53 }, -1 },{ { 29, 54 }, -1 },{ { 29, 55 }, -1 },{ { 29, 56 }, -1 },{ { 29, 57 }, -1 },{ { 29, 58 }, -1 },{ { 29, 59 }, -1 },{ { 29, 60 }, -1 },{ { 29, 61 }, -1 },{ { 29, 62 }, -1 },{ { 29, 63 }, -1 },{ { 29, 80 }, -1 },{ { 29, 108 }, -1 },{ { 29, 128 }, -1 },{ { 30, 16 }, -1 },{ { 30, 34 }, -1 },{ { 30, 63 }, -1 },{ { 30, 80 }, -1 },{ { 30, 108 }, -1 },{ { 30, 128 }, -1 },{ { 31, 16 }, -1 },{ { 31, 34 }, -1 },{ { 31, 63 }, -1 },{ { 31, 80 }, -1 },{ { 31, 108 }, -1 },{ { 31, 128 }, -1 },{ { 32, 16 }, -1 },{ { 32, 34 }, -1 },{ { 32, 63 }, -1 },{ { 32, 80 }, -1 },{ { 32, 108 }, -1 },{ { 32, 128 }, -1 },{ { 33, 16 }, -1 },{ { 33, 34 }, -1 },{ { 33, 63 }, -2 },{ { 33, 64 }, -1 },{ { 33, 65 }, -1 },{ { 33, 66 }, -1 },{ { 33, 67 }, -1 },{ { 33, 68 }, -1 },{ { 33, 69 }, -1 },{ { 33, 70 }, -1 },{ { 33, 71 }, -1 },{ { 33, 72 }, -1 },{ { 33, 73 }, -1 },{ { 33, 74 }, -1 },{ { 33, 75 }, -1 },{ { 33, 76 }, -1 },{ { 33, 77 }, -1 },{ { 33, 78 }, -1 },{ { 33, 79 }, -1 },{ { 33, 80 }, -1 },{ { 33, 81 }, -1 },{ { 33, 82 }, -1 },{ { 33, 83 }, -1 },{ { 33, 84 }, -1 },{ { 33, 85 }, -1 },{ { 33, 86 }, -1 },{ { 33, 87 }, -1 },{ { 33, 88 }, -1 },{ { 33, 89 }, -1 },{ { 33, 90 }, -1 },{ { 33, 91 }, -1 },{ { 33, 92 }, -1 },{ { 33, 93 }, -1 },{ { 33, 94 }, -1 },{ { 33, 95 }, -1 },{ { 33, 96 }, -1 },{ { 33, 97 }, -1 },{ { 33, 98 }, -1 },{ { 33, 99 }, -1 },{ { 33, 100 }, -1 },{ { 33, 101 }, -1 },{ { 33, 102 }, -1 },{ { 33, 103 }, -1 },{ { 33, 104 }, -1 },{ { 33, 105 }, -1 },{ { 33, 106 }, -1 },{ { 33, 107 }, -1 },{ { 33, 108 }, -1 },{ { 33, 109 }, -1 },{ { 33, 110 }, -1 },{ { 33, 111 }, -1 },{ { 33, 112 }, -1 },{ { 33, 113 }, -1 },{ { 33, 114 }, -1 },{ { 33, 115 }, -1 },{ { 33, 116 }, -1 },{ { 33, 117 }, -1 },{ { 33, 118 }, -1 },{ { 33, 119 }, -1 },{ { 33, 120 }, -1 },{ { 33, 121 }, -1 },{ { 33, 122 }, -1 },{ { 33, 123 }, -1 },{ { 33, 124 }, -1 },{ { 33, 125 }, -1 },{ { 33, 126 }, -1 },{ { 33, 127 }, -1 },{ { 33, 128 }, -2 },{ { 33, 129 }, -1 },{ { 33, 130 }, -1 },{ { 33, 131 }, -1 },{ { 33, 132 }, -1 },{ { 33, 133 }, -1 },{ { 33, 134 }, -1 },{ { 33, 135 }, -1 },{ { 33, 136 }, -1 },{ { 33, 137 }, -1 },{ { 33, 138 }, -1 },{ { 33, 139 }, -1 },{ { 33, 140 }, -1 },{ { 34, 16 }, -1 },{ { 34, 34 }, -1 },{ { 34, 63 }, -1 },{ { 34, 110 }, -1 },{ { 34, 140 }, -1 },{ { 35, 8 }, 10 },{ { 35, 16 }, -1 },{ { 35, 34 }, -1 },{ { 35, 63 }, -1 },{ { 35, 110 }, -1 },{ { 35, 140 }, -1 },{ { 35, 148 }, 7 },{ { 36, 8 }, -1 },{ { 36, 16 }, -1 },{ { 36, 34 }, -1 },{ { 36, 63 }, -1 },{ { 36, 110 }, -1 },{ { 36, 140 }, -1 },{ { 36, 148 }, -1 },{ { 37, 8 }, -1 },{ { 37, 16 }, -1 },{ { 37, 34 }, -1 },{ { 37, 63 }, -1 },{ { 37, 110 }, -1 },{ { 37, 140 }, -1 },{ { 37, 148 }, -1 },{ { 38, 8 }, -1 },{ { 38, 16 }, -1 },{ { 38, 34 }, -1 },{ { 38, 63 }, -1 },{ { 38, 110 }, -1 },{ { 38, 140 }, -1 },{ { 38, 148 }, -1 },{ { 39, 8 }, -1 },{ { 39, 9 }, -1 },{ { 39, 10 }, -1 },{ { 39, 11 }, -1 },{ { 39, 12 }, -1 },{ { 39, 13 }, -1 },{ { 39, 14 }, -1 },{ { 39, 15 }, -1 },{ { 39, 16 }, -1 },{ { 39, 34 }, -1 },{ { 39, 63 }, -1 },{ { 39, 110 }, 1 },{ { 39, 140 }, -1 },{ { 39, 141 }, -1 },{ { 39, 142 }, -1 },{ { 39, 143 }, -1 },{ { 39, 144 }, -1 },{ { 39, 145 }, -1 },{ { 39, 146 }, -1 },{ { 39, 147 }, -1 },{ { 39, 148 }, -1 },{ { 40, 16 }, -1 },{ { 40, 34 }, -1 },{ { 40, 63 }, -1 },{ { 40, 140 }, -1 },{ { 41, 16 }, -1 },{ { 41, 34 }, -1 },{ { 41, 63 }, -1 },{ { 41, 140 }, -1 },{ { 42, 16 }, -1 },{ { 42, 34 }, -1 },{ { 42, 63 }, -1 },{ { 42, 140 }, -1 },{ { 43, 16 }, -1 },{ { 43, 34 }, -1 },{ { 43, 63 }, -1 },{ { 43, 140 }, -1 },{ { 44, 16 }, -1 },{ { 44, 34 }, -1 },{ { 44, 46 }, 2 },{ { 44, 63 }, -1 },{ { 44, 140 }, -1 },{ { 45, 16 }, -1 },{ { 45, 34 }, -1 },{ { 45, 46 }, -1 },{ { 45, 63 }, -1 },{ { 45, 140 }, -1 },{ { 46, 16 }, -1 },{ { 46, 34 }, -1 },{ { 46, 46 }, -1 },{ { 46, 63 }, -1 },{ { 46, 140 }, -1 },{ { 47, 16 }, -1 },{ { 47, 34 }, -1 },{ { 47, 46 }, -1 },{ { 47, 63 }, -1 },{ { 47, 140 }, -1 },{ { 48, 16 }, -1 },{ { 48, 34 }, -1 },{ { 48, 46 }, -1 },{ { 48, 63 }, -1 },{ { 48, 140 }, -1 },{ { 49, 16 }, -1 },{ { 49, 34 }, -1 },{ { 49, 46 }, -1 },{ { 49, 63 }, -1 },{ { 49, 140 }, -1 },{ { 50, 1 }, -1 },{ { 50, 2 }, -1 },{ { 50, 3 }, -1 },{ { 50, 4 }, -1 },{ { 50, 5 }, -1 },{ { 50, 6 }, -1 },{ { 50, 7 }, -1 },{ { 50, 8 }, -1 },{ { 50, 9 }, -1 },{ { 50, 10 }, -1 },{ { 50, 11 }, -1 },{ { 50, 12 }, -1 },{ { 50, 13 }, -1 },{ { 50, 14 }, -1 },{ { 50, 15 }, -1 },{ { 50, 16 }, -1 },{ { 50, 17 }, -1 },{ { 50, 18 }, -1 },{ { 50, 19 }, -1 },{ { 50, 20 }, -1 },{ { 50, 21 }, -1 },{ { 50, 22 }, -1 },{ { 50, 23 }, -1 },{ { 50, 24 }, -1 },{ { 50, 25 }, -1 },{ { 50, 26 }, -1 },{ { 50, 27 }, -1 },{ { 50, 28 }, -1 },{ { 50, 29 }, -1 },{ { 50, 30 }, -1 },{ { 50, 31 }, -1 },{ { 50, 32 }, -1 },{ { 50, 33 }, -1 },{ { 50, 34 }, -1 },{ { 50, 35 }, -1 },{ { 50, 36 }, -1 },{ { 50, 37 }, -1 },{ { 50, 38 }, -1 },{ { 50, 39 }, -2 },{ { 50, 40 }, -1 },{ { 50, 41 }, -1 },{ { 50, 42 }, -1 },{ { 50, 43 }, -1 },{ { 50, 44 }, -1 },{ { 50, 45 }, -1 },{ { 50, 46 }, -1 },{ { 50, 47 }, -1 },{ { 50, 48 }, -1 },{ { 50, 49 }, -1 },{ { 50, 50 }, -1 },{ { 50, 51 }, -1 },{ { 50, 52 }, -1 },{ { 50, 53 }, -1 },{ { 50, 54 }, -1 },{ { 50, 55 }, -1 },{ { 50, 56 }, -1 },{ { 50, 57 }, -1 },{ { 50, 58 }, -1 },{ { 50, 59 }, -1 },{ { 50, 60 }, -1 },{ { 50, 61 }, -1 },{ { 50, 62 }, -1 },{ { 50, 63 }, -1 },{ { 50, 64 }, -1 },{ { 50, 65 }, -1 },{ { 50, 66 }, -1 },{ { 50, 67 }, -1 },{ { 50, 68 }, -1 },{ { 50, 69 }, -1 },{ { 50, 70 }, -1 },{ { 50, 71 }, -1 },{ { 50, 72 }, -1 },{ { 50, 73 }, -1 },{ { 50, 74 }, -1 },{ { 50, 75 }, -1 },{ { 50, 76 }, -1 },{ { 50, 77 }, -1 },{ { 50, 78 }, -1 },{ { 50, 79 }, -1 },{ { 50, 80 }, -1 },{ { 50, 81 }, -1 },{ { 50, 82 }, -1 },{ { 50, 83 }, -1 },{ { 50, 84 }, -1 },{ { 50, 85 }, -1 },{ { 50, 86 }, -1 },{ { 50, 87 }, -1 },{ { 50, 88 }, -1 },{ { 50, 89 }, 1 },{ { 50, 140 }, -1 },{ { 51, 6 }, -1 },{ { 51, 40 }, -1 },{ { 51, 65 }, -1 },{ { 51, 140 }, -1 },{ { 52, 6 }, -1 },{ { 52, 40 }, -1 },{ { 52, 65 }, -1 },{ { 52, 140 }, -1 },{ { 53, 6 }, -1 },{ { 53, 40 }, -1 },{ { 53, 65 }, -1 },{ { 53, 140 }, -1 },{ { 54, 6 }, -1 },{ { 54, 40 }, -1 },{ { 54, 65 }, -1 },{ { 54, 140 }, -1 },{ { 55, 6 }, 5 },{ { 55, 40 }, -1 },{ { 55, 65 }, -1 },{ { 55, 140 }, -1 },{ { 56, 40 }, -1 },{ { 56, 65 }, -1 },{ { 56, 140 }, -1 },{ { 57, 40 }, -1 },{ { 57, 65 }, -1 },{ { 57, 140 }, -1 },{ { 58, 40 }, -1 },{ { 58, 65 }, -1 },{ { 58, 140 }, -1 },{ { 59, 40 }, -1 },{ { 59, 65 }, -1 },{ { 59, 140 }, -1 },{ { 60, 40 }, -1 },{ { 60, 65 }, -1 },{ { 60, 140 }, -1 },{ { 61, 40 }, -1 },{ { 61, 65 }, -1 },{ { 61, 140 }, -1 },};

// level settings
vector<vector<int>> levels={{1,4,120},{2,3,120},{3,1,150},{3,1,120}};
vector<vector<int>> coins_giver={{40,10},{45,15},{50,20},{55,25}};
vector<int> diamonds_giver={5,10,15,20};

// Enum for different game states/screens
typedef enum {
    MAIN_MENU,
    ABOUT_SCREEN,
    HELP_SCREEN,
    PLAY_SCREEN,
    WIN_SCREEN,
    GAME_OVER
} GameState;

// enum for different character positions
typedef enum {
    UP,
    DOWN,
    FRONT,
    BACK
} Character;
Character char_state=FRONT;
// Enum for button actions
typedef enum {
    NO_ACTION,
    ABOUT_PRESSED,
    HELP_PRESSED,
    PLAY_PRESSED
} ButtonAction;

// Save progress to internal storage
static void SaveGameProgress(int coins, int diamonds, int level)
{
    // Format as plain text: "coins diamonds level"
    char buffer[64];
    sprintf(buffer, "%d %d %d", coins, diamonds, level);
    // Writes to "<internal>/savegame.dat"
    SaveFileText("savegame.dat", buffer);
}

// Load progress; returns true if file existed
static bool LoadGameProgress(int &coins, int &diamonds, int &level)
{
    if (!FileExists("savegame.dat")) return false;
    char *data = LoadFileText("savegame.dat");
    sscanf(data, "%d %d %d", &coins, &diamonds, &level);
    UnloadFileText(data);
    return true;
}

void reset(float& elapsedTime) {
    treasures = 0;
    penalty = 0;
    elapsedTime = levels[level][2];
    playerClue = clue_giver(-1);
    playerX = 2810-2012;
    playerY = 4305-3935 ;
}

void DrawTopRightButton() {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int btnSize = screenH * 0.05f; // 5% of screen height
    int padding = 20; // Optional: space from edge

    int btnX = screenW - btnSize - padding;
    int btnY = padding;

    // Draw button (you can change color/text as needed)
    DrawRectangle(btnX, btnY, btnSize, btnSize, DARKBLUE);

    // Draw icon or text (optional)
    int fontSize = btnSize * 0.5f;
    const char* btnLabel = "<";
    int textWidth = MeasureText(btnLabel, fontSize);
    DrawText(btnLabel, btnX + (btnSize - textWidth) / 2, btnY + (btnSize - fontSize) / 2, fontSize, WHITE);
}
bool IsTopRightButtonPressed() {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int btnSize = screenH * 0.05f;
    int padding = 20;

    int btnX = screenW - btnSize - padding;
    int btnY = padding;

    Vector2 inputPos;
    bool inputActive = false;

#if defined(PLATFORM_ANDROID) || defined(PLATFORM_WEB)
    if (GetTouchPointCount() > 0) {
        inputPos = GetTouchPosition(0);
        inputActive = true;
    }
#else
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        inputPos = GetMousePosition();
        inputActive = true;
    }
#endif

    if (inputActive) {
        Rectangle btnRect = { (float)btnX, (float)btnY, (float)btnSize, (float)btnSize };
        if (CheckCollisionPointRec(inputPos, btnRect)) return true;
    }
    return false;
}

// Function to draw the starting window with a margin and responsive sizing
void DrawStartingWindow()
{
    int h = GetScreenHeight();
    int w = GetScreenWidth();

    // Upper left box dimensions (TREASURE HUNT)
    int boxWidth = w * 0.5;
    int boxHeight = h * 0.2;

    // 5% margin inside the box
    int marginX = boxWidth * 0.05;
    int marginY = boxHeight * 0.05;

    // Inner box dimensions after margin
    int innerBoxWidth = boxWidth - 2 * marginX;
    int innerBoxHeight = boxHeight - 2 * marginY;

    // Start with font size as inner box height
    int fontSize = innerBoxHeight;

    // Scale font size so text fits within inner box width
    int textWidth = MeasureText("TREASURE HUNT", fontSize);
    while (textWidth > innerBoxWidth && fontSize > 1) {
        fontSize--;
        textWidth = MeasureText("TREASURE HUNT", fontSize);
    }

    // Right side area dimensions for coins and diamonds
    int rightAreaX = boxWidth;
    int rightAreaWidth = w - boxWidth;
    int rightAreaHeight = boxHeight;

    // Button dimensions (20% of screen width for both width and height)
    int buttonWidth = w * 0.2;
    int buttonHeight = h * 0.2;

    // Calculate button positions for symmetric placement
    int totalButtonsWidth = 3 * buttonWidth;
    int remainingSpace = w - totalButtonsWidth;
    int buttonSpacing = remainingSpace / 4;  // 4 gaps: before first, between buttons, after last

    int button1X = buttonSpacing;
    int button2X = button1X + buttonWidth + buttonSpacing;
    int button3X = button2X + buttonWidth + buttonSpacing;
    int buttonY = h - buttonHeight - (h * 0.05);  // 5% margin from bottom

    // BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw upper left bounding box (optional, for reference)
    DrawRectangle(0, 0, boxWidth, boxHeight, Fade(LIGHTGRAY, 0.2f));

    // Draw the TREASURE HUNT text with margin, vertically centered
    int textX = marginX;
    int textY = marginY + (innerBoxHeight - fontSize) / 2;
    DrawText("TREASURE HUNT", textX, textY, fontSize, RED);

    // Draw right area background (optional, for reference)
    DrawRectangle(rightAreaX, 0, rightAreaWidth, rightAreaHeight, Fade(GRAY, 0.3f));

    // Calculate font size for coins and diamonds (smaller than main title)
    int resourceFontSize = rightAreaHeight*0.25 ;
    int resourceTextY = rightAreaHeight*0.35;
    DrawText(TextFormat("LEVEL:%d",level), boxWidth+0.05*rightAreaWidth, resourceTextY, resourceFontSize, GREEN);
    DrawText(TextFormat("COINS:%d",coins), boxWidth+0.32*rightAreaWidth, resourceTextY, resourceFontSize, GOLD);
    DrawText(TextFormat("DIAMONDS:%d",diamonds), boxWidth+0.62*rightAreaWidth, resourceTextY, resourceFontSize, BLUE);

    // Draw buttons with backgrounds
    Color buttonColor = GRAY;
    Color buttonTextColor = WHITE;
    int buttonTextSize = buttonHeight * 0.15;

    // About button
    DrawRectangle(button1X, buttonY, buttonWidth, buttonHeight, buttonColor);
    DrawRectangleLines(button1X, buttonY, buttonWidth, buttonHeight, BLACK);
    int aboutTextWidth = MeasureText("ABOUT", buttonTextSize);
    DrawText("ABOUT",
             button1X + (buttonWidth - aboutTextWidth) / 2,
             buttonY + (buttonHeight - buttonTextSize) / 2,
             buttonTextSize, buttonTextColor);

    // Help button
    DrawRectangle(button3X, buttonY, buttonWidth, buttonHeight, buttonColor);
    DrawRectangleLines(button3X, buttonY, buttonWidth, buttonHeight, BLACK);
    int helpTextWidth = MeasureText("HELP", buttonTextSize);
    DrawText("HELP",
             button3X + (buttonWidth - helpTextWidth) / 2,
             buttonY + (buttonHeight - buttonTextSize) / 2,
             buttonTextSize, buttonTextColor);

    // Play button
    DrawRectangle(button2X, buttonY, buttonWidth, buttonHeight, GREEN);
    DrawRectangleLines(button2X, buttonY, buttonWidth, buttonHeight, BLACK);
    int playTextWidth = MeasureText("PLAY", buttonTextSize);
    DrawText("PLAY",
             button2X + (buttonWidth - playTextWidth) / 2,
             buttonY + (buttonHeight - buttonTextSize) / 2,
             buttonTextSize, WHITE);

}

// Function to detect button presses using touch input
ButtonAction HandleButtonPress() {
    int h = GetScreenHeight();
    int w = GetScreenWidth();

    // Button dimensions (matching your DrawStartingWindow layout)
    int buttonWidth = w * 0.2;
    int buttonHeight = h * 0.2;

    // Calculate button positions (same logic as DrawStartingWindow)
    int totalButtonsWidth = 3 * buttonWidth;
    int remainingSpace = w - totalButtonsWidth;
    int buttonSpacing = remainingSpace / 4;

    int button1X = buttonSpacing;                                    // About
    int button2X = buttonSpacing + buttonWidth + buttonSpacing;     // Play
    int button3X = buttonSpacing + 2 * (buttonWidth + buttonSpacing); // Help
    int buttonY = h - buttonHeight - (h * 0.05);

    // Create button rectangles
    Rectangle aboutButton = {(float)button1X, (float)buttonY, (float)buttonWidth, (float)buttonHeight};
    Rectangle playButton = {(float)button2X, (float)buttonY, (float)buttonWidth, (float)buttonHeight};
    Rectangle helpButton = {(float)button3X, (float)buttonY, (float)buttonWidth, (float)buttonHeight};

    // Check for touch input (Android) or mouse input (desktop testing)
    Vector2 inputPos = {0, 0};
    bool inputDetected = false;

    // Primary: Android touch input
    if (IsGestureDetected(GESTURE_TAP)) {
        inputPos = GetTouchPosition(0);
        inputDetected = true;
    }
        // Fallback: Desktop mouse input for testing
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        inputPos = GetMousePosition();
        inputDetected = true;
    }

    // Check collision detection
    if (inputDetected) {
        if (CheckCollisionPointRec(inputPos, aboutButton)) {
            return ABOUT_PRESSED;
        }
        else if (CheckCollisionPointRec(inputPos, helpButton)) {
            return HELP_PRESSED;
        }
        else if (CheckCollisionPointRec(inputPos, playButton)) {
            return PLAY_PRESSED;
        }
    }

    return NO_ACTION;
}

// Function to draw About screen
void DrawAboutScreen() {
    int h = GetScreenHeight();
    int w = GetScreenWidth();

    // BeginDrawing();
    ClearBackground(SKYBLUE);

    // Title
    int titleFontSize = h * 0.08;
    int titleWidth = MeasureText("ABOUT", titleFontSize);
    DrawText("ABOUT", (w - titleWidth) / 2, h * 0.2, titleFontSize, DARKBLUE);

    // Content
    int contentFontSize = h * 0.04;
    DrawText("About Treasure Hunt Game", w * 0.1, h * 0.4, contentFontSize, BLACK);
    DrawText("Explore the campus and find treasures!", w * 0.1, h * 0.5, contentFontSize, BLACK);
    DrawText("Solve clues to progress through the game", w * 0.1, h * 0.6, contentFontSize, BLACK);

    // Back instruction
    int backFontSize = h * 0.03;
    DrawText("Touch anywhere to return to menu", w * 0.1, h * 0.8, backFontSize, GRAY);

    // EndDrawing();
    DrawTopRightButton();
}

void DrawHelpScreen() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    ClearBackground(RAYWHITE);

    // Title
    DrawText("HELP SCREEN (3D)", screenWidth/2 - MeasureText("HELP SCREEN (3D)", 30)/2, 20, 30, DARKGRAY);

    // 3D Camera setup (static for simplicity)
    static Camera3D camera = { 0 };
    static bool cameraInit = false;
    if (!cameraInit) {
        camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
        cameraInit = true;
    }

    // Camera smooth auto-rotate
    static float t = 0.0f;
    t += GetFrameTime() * 0.5f;
    camera.position.x = cosf(t) * 6.0f;
    camera.position.z = sinf(t) * 6.0f;

    BeginMode3D(camera);
    // 3D cuboid
    DrawCube((Vector3){0,0,0}, 3,2,1.5, BLUE);
    DrawCubeWires((Vector3){0,0,0}, 3,2,1.5, DARKBLUE);

    // Optional: extra cube for fun
    DrawCube((Vector3){1.5f,1.0f,0}, 1,1,1, RED);
    DrawCubeWires((Vector3){1.5f,1.0f,0}, 1,1,1, BLACK);

    DrawGrid(10, 1.0f);
    EndMode3D();

    // 2D instructions
    DrawRectangle(10,screenHeight-80,screenWidth-20,70, Fade(GRAY,0.3f));
    DrawText("3D Cuboid demo: Blue cuboid, Red cube (Help Screen)", 20, screenHeight-70, 18, DARKGRAY);
    DrawText("Back jane ke liye top-right button press kro.", 20, screenHeight-45, 16, GRAY);

    // Return button - apne project ke hisaab se
    DrawTopRightButton();
}

void InitGame(int screenWidth, int screenHeight) {
    // Initialize player at center
    playerX = 2810-2012;
    playerY = 4305-3935 ;

    // Initialize camera
    camera.target = (Vector2){ playerX, playerY };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight * 0.55f };
    camera.rotation = 0.0f;
    camera.zoom = 2.5f;

    // Joystick sizes and position (10% of width & height)
    joystickBaseRadius = screenWidth * 0.15f / 2.0f;
    joystickRadius = joystickBaseRadius * 0.4f;
    joystickCenter = (Vector2){ joystickBaseRadius + 20, screenHeight - joystickBaseRadius - 20 };
}
int WorldToTileX(float worldX) { return (int)(worldX / 70); }
int WorldToTileY(float worldY) { return (int)(worldY / 70); }

// Function to draw Play/Game screen
void DrawPlayScreen(Music& nit,float& timer,int& factor,Sound& treas,Sound& pen,Music& skateboard,Texture2D& playerTexture,Texture2D& mapTexture, float& elapsedTime) {
    ClearBackground(GREEN);
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    // Calculate split areas
    int statsH = screenH * 0.10f;   // 10%
    int gameY = statsH;
    int gameH = screenH - statsH;   // 90%

    // --- BEFORE applying joystick movement, compute desired pos ---
    float speed = 100 * GetFrameTime() * factor;
    float desiredX = playerX;
    float desiredY = playerY;

    if (joystickActive) {
        if(!st&&IsMusicValid(skateboard)){
            PlayMusicStream(skateboard);
            st=true;
        }
        if(IsMusicValid(skateboard)) UpdateMusicStream(skateboard);
        desiredX += joystickDirection.x * speed;
        desiredY += joystickDirection.y * speed;
    }
    if(abs(desiredX-playerX)<abs(desiredY-playerY)){
        if(desiredY>playerY) char_state=DOWN;
        else char_state=UP;
    }
    else{
        if(desiredX<playerX) char_state=BACK;
        else char_state=FRONT;
    }
    // Convert desired positions to tile coordinates
    int tileX = WorldToTileX(desiredX + (float) 2012);
    int tileY = WorldToTileY(desiredY + (float) 3935);
    int tX = WorldToTileX(playerX + (float) 2012);
    int tY = WorldToTileY(playerY + (float) 3935);
    int bid=INT_MIN;
    // If the destination tile is a road, commit movement
    if (tileMap.count({tileY, tileX})) {
        playerX = desiredX;
        playerY = desiredY;
        if(!nitroOn&&tileMap[{tileY, tileX}] == -2){
            nitro=true;
        }
        else nitro=false;
        if (tileMap[{tileY, tileX}] != -1&&tileMap[{tileY, tileX}] != -2) {
            see = true;
            bid = tileMap[{tileY, tileX}];
        } else {
            see = false;
            still = false;
        }
    } else if (tileMap.count({tileY, tX})) {
        playerY = desiredY;
        if(!nitroOn&&tileMap[{tileY, tX}] == -2){
            nitro=true;
        }
        else nitro=false;
        if (tileMap[{tileY, tX}] != -1&&tileMap[{tileY, tX}] != -2) {
            see = true;
            bid = tileMap[{tileY, tX}];
        } else {
            see = false;
            still = false;
        }
    } else if (tileMap.count({tY, tileX})) {
        playerX = desiredX;
        if(!nitroOn&&tileMap[{tY, tileX}] == -2){
            nitro=true;
        }
        else nitro=false;
        if (tileMap[{tY, tileX}] != -1&&tileMap[{tY, tileX}] != -2) {
            see = true;
            bid = tileMap[{tY, tileX}];
        } else {
            see = false;
            still = false;
        }
    }

    // Update camera to follow player
    if (joystickActive) {
        camera.target = (Vector2) {playerX, playerY};
    }

    ClearBackground(RAYWHITE);

    // ---- TOP 10%: Stats Area ----
    DrawRectangle(0, 0, screenW, statsH, Fade(DARKGRAY, 0.8f));
    int statsFont = statsH * 0.4f;
    int statsY = (statsH - statsFont) / 2;
    int minutes = (int) elapsedTime / 60;
    int seconds = (int) elapsedTime % 60;
    int min = (int) levels[level][2] / 60;
    int sec = (int) levels[level][2] % 60;
    DrawText(TextFormat("Treasures: %d/%d", treasures, levels[level][0]), screenW * 0.05f, statsY,
             statsFont, GOLD);
    DrawText(TextFormat("Penalty: %d/%d", penalty, levels[level][1]), screenW * 0.35f, statsY,
             statsFont, RED);
    DrawText(TextFormat("Time: %02d:%02d/%02d:%02d", minutes, seconds, min, sec), screenW * 0.65f,
             statsY, statsFont, WHITE);
    // ---- BOTTOM 90%: Game Area ----
    BeginScissorMode(0, gameY, screenW, gameH);
    BeginMode2D(camera);

    // --- Draw the map image as background ---
    // Adjust destRect as needed to fit your world coordinates
    Rectangle srcRect = {0, 0, (float) mapTexture.width, (float) mapTexture.height};
    Rectangle destRect = {-2012, -3935, (float) mapTexture.width, (float) mapTexture.height};
    DrawTexturePro(mapTexture, srcRect, destRect, (Vector2) {0, 0}, 0.0f, WHITE);

    for (auto it: tileMap) {
        if (it.second == -1)
            DrawRectangle(it.first.second * 70 - 2012, it.first.first * 70 - 3935, 70, 70, GRAY);
        else if(it.second==-2)
            DrawRectangle(it.first.second * 70 - 2012, it.first.first * 70 - 3935, 70, 70, SKYBLUE);
        else DrawRectangle(it.first.second * 70 - 2012, it.first.first * 70 - 3935, 70, 70, GOLD);
    }
    // Draw player
    int a=1;
    float r;
    if(char_state==UP){
        a=1;r=-90.0f;
    }
    else if(char_state==DOWN){
        a=1;r=90.0f;
    }
    else if(char_state==FRONT){
        a=1;r=0.0f;
    }
    else{
        a=-1;r=0.0f;
    }
    Rectangle sourceRec = {0, 0, a*(float)playerTexture.width, (float)playerTexture.height};
    Rectangle destRec = {playerX, playerY, playerTexture.width * 0.1f,playerTexture.height * 0.1f};
    Vector2 origin = {fabsf(destRec.width) * 0.5f, fabsf(destRec.height) * 0.95f};// Center the texture
    DrawTexturePro(playerTexture, sourceRec, destRec, origin,r, WHITE);

    EndMode2D();
    EndScissorMode();

    // ---- Joystick on bottom-left ----
    DrawCircleV(joystickCenter, joystickBaseRadius, Fade(GRAY, 0.6f));
    Vector2 knobPos = {
            joystickCenter.x + joystickDirection.x * (joystickBaseRadius - joystickRadius),
            joystickCenter.y + joystickDirection.y * (joystickBaseRadius - joystickRadius)
    };
    DrawCircleV(knobPos, joystickRadius, DARKGRAY);

    // Process touch for joystick
    if (IsGestureDetected(GESTURE_DRAG) || IsGestureDetected(GESTURE_HOLD)) {
        Vector2 touch = GetTouchPosition(0);
        float dist = Vector2Distance(touch, joystickCenter);
        if (dist < joystickBaseRadius) {
            joystickActive = true;
            joystickDirection = Vector2Normalize(Vector2Subtract(touch, joystickCenter));
        }
    }
    if (GetTouchPointCount() == 0) {
        joystickActive = false;
        joystickDirection = (Vector2) {0, 0};
        StopMusicStream(skateboard);
        st=false;
    }

    DrawRectangle(0.0f, screenH * 0.11, screenW, screenH * 0.05f, Fade(YELLOW, 0.6f));
    DrawText(TextFormat("%s", playerClue.c_str()), screenW * 0.05f, screenH * 0.11, screenH * 0.05f,BLACK);
    if(nitro){
        DrawRectangle(screenW*0.79,screenH*0.89,screenW*0.2,screenH*0.1,SKYBLUE);
        DrawText("NITRO [5 coins]",screenW*0.795,screenH*0.895,screenH*0.045,RAYWHITE);
    }
    if (see) {
        int bh = screenW * 0.6f;
        int bw = screenH * 0.16f;
        DrawRectangle(bh, bw, screenW - bh, (screenH * 0.3f), Fade(BLUE, 0.6f));
        if(bid==6)DrawText(TextFormat("%s", name[bid].c_str()), (int) (screenW * 0.61f),
                           (int) (screenH * .165f), (int) (screenH * .06f), GOLD);
        else{
            DrawText(TextFormat("%s", name[bid].c_str()), (int) (screenW * 0.61f),
                     (int) (screenH * .165f), (int) (screenH * .08f), GOLD);
        }
        if(!still){
            DrawRectangle((screenW * 0.62f), (screenH * 0.32f), (screenW * 0.16f), (screenH * 0.1f),
                          YELLOW);
            DrawText("CHECK", (screenW * 0.62f), (screenH * 0.32f), (screenH * 0.1f), ORANGE);
        }
        if (still) {
            DrawRectangle(bh, (screenH * 0.32f), screenW - bh,
                          (screenH * 0.045f), YELLOW);
            if (pbid == 1) {
                DrawText("CONGRATS!! YOU FOUND A TREASURE .", (int) (screenW * 0.605f),
                         (int) (screenH * 0.32f),
                         (int) (screenH * .045f), GREEN);
            }
            else {
                DrawText("OOPS!! YOU GOT A PENALTY .", (int) (screenW * 0.605f),
                         (int) (screenH * 0.32f),
                         (int) (screenH * .045f), RED);
            }
        }
    }

    // --- CAMERA AND GESTURE HANDLING ---
    Vector2 touchPos = {0, 0};
    bool inputActive = false;

#if defined(PLATFORM_ANDROID) || defined(PLATFORM_WEB)
    int points = GetTouchPointCount();
    if (points > 0) {
        touchPos = GetTouchPosition(0);
        inputActive = true;
    }
    if (points == 1) {
        Vector2 curr = GetTouchPosition(0);

        // Only pan if not touching joystick
        float distToJoystick = Vector2Distance(curr, joystickCenter);
        bool inJoystick = (distToJoystick < joystickBaseRadius);

        if (!inJoystick) {
            if (wasPanning) {
                Vector2 delta = Vector2Subtract(curr, prevTouch1);
                camera.target.x -= delta.x / camera.zoom;
                camera.target.y -= delta.y / camera.zoom;
            }
            prevTouch1 = curr;
            wasPanning = true;
        } else {
            wasPanning = false;
        }
        wasPinching = false;
    }
    else if (points == 2) {
        Vector2 t1 = GetTouchPosition(0);
        Vector2 t2 = GetTouchPosition(1);
        float currDist = Vector2Distance(t1, t2);

        if (wasPinching) {
            float deltaDist = currDist - prevPinchDist;
            camera.zoom += deltaDist * 0.005f; // Adjust sensitivity as needed
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
            if (camera.zoom > 10.0f) camera.zoom = 10.0f;
        }
        prevPinchDist = currDist;
        prevTouch1 = t1;
        prevTouch2 = t2;
        wasPinching = true;
        wasPanning = false;
    }
    else {
        wasPanning = false;
        wasPinching = false;
    }
#endif


    if (inputActive) {
        Rectangle check = {(screenW * 0.62f), (screenH * 0.32f), (screenW * 0.16f), (screenH * 0.1f)};
        if (!still && see && CheckCollisionPointRec(touchPos, check)) {
            if (identity_checker(playerClue, identities[bid])) {
                PlaySound(treas);
                treasures++;
                playerClue = clue_giver(bid);
                pbid = 1;
            } else {
                PlaySound(pen);
                penalty++;
                pbid = 0;
            }
            still = true;
        }
        Rectangle nitr = {screenW*0.79f,screenH*0.89f,screenW*0.2f,screenH*0.1f};
        if(!nitroOn&&nitro&&CheckCollisionPointRec(touchPos,nitr)){
            if(IsMusicValid(nit))PlayMusicStream(nit);
            nitroOn=true;
            coins-=5;
            timer=15.0f;
            nitro=false;
        }
    }

    DrawTopRightButton();
}

enum EndScreenType {
    WIN_SCREENn, GAME_OVER_SCREEN
};

struct EndScreenResult {
    bool mainMenuPressed = false;
    bool actionPressed = false; // "Next" for win, "Restart" for game over
};

// type: WIN_SCREEN ya GAME_OVER_SCREEN
void DrawEndScreenUI(EndScreenType type,int& c,int& ds) {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    // 70% size, centered
    int winW = screenW * 0.7f;
    int winH = screenH * 0.7f;
    int winX = (screenW - winW) / 2;
    int winY = (screenH - winH) / 2;

    // Dimmed background
    DrawRectangle(0, 0, screenW, screenH, Fade(BLACK, 0.5f));
    // Window background
    DrawRectangle(winX, winY, winW, winH, RAYWHITE);

    // Title and colors
    const char *title = (type == WIN_SCREENn) ? "You Won" : "Game Over";
    Color titleColor = (type == WIN_SCREENn) ? GREEN : RED;
    int fontSize = winH / 10;
    int textWidth = MeasureText(title, fontSize);
    int textX = winX + (winW-textWidth)/2;
    int textY = winY + winH*0.1;
    DrawText(title, textX, textY, fontSize, titleColor);

    c=max(0,treasures*coins_giver[level-1][0]-penalty*coins_giver[level][1]);
    ds=(type==WIN_SCREENn)?diamonds_giver[level-1]:0;
    // Calculate font size for coins and diamonds (smaller than main title)
    int resourceFontSize = winH * 0.07;
    // Prepare label strings
    char coinsLabel[32], diamondsLabel[32];
    sprintf(coinsLabel, "COINS: %d", c);
    sprintf(diamondsLabel, "DIAMONDS: %d", ds);
    // Measure text widths
    int coinsTextW = MeasureText(coinsLabel, resourceFontSize);
    int diamondsTextW = MeasureText(diamondsLabel, resourceFontSize);
    // Calculate horizontal positions to place side by side
    float coinsX = (screenW-coinsTextW)/2;
    float diamondsX = (screenW-diamondsTextW)/2;
    // Draw Coins label
    DrawText(coinsLabel, coinsX, screenH*0.4, resourceFontSize, GOLD);
    // Draw Diamonds label
    DrawText(diamondsLabel, diamondsX, screenH*0.5, resourceFontSize, SKYBLUE);

    // Button sizes and positions
    int btnW = screenW * 0.25f;
    int btnH = screenH * 0.1f;
    int mainMenuX = winX + winW / 4 - btnW / 2;
    int mainMenuY = winY + winH * 3 / 4;
    int actionX = winX + winW * 3 / 4 - btnW / 2;
    int actionY = mainMenuY;

    // Draw Main Menu button
    DrawRectangle(mainMenuX, mainMenuY, btnW, btnH, BLUE);
    int mmTextW = MeasureText("Main Menu", btnH * 0.5f);
    DrawText("Main Menu", mainMenuX + (btnW - mmTextW) / 2,
             mainMenuY + (btnH - btnH * 0.5f) / 2, btnH * 0.5f, WHITE);

    // Draw Action button ("Next" or "Restart")
    const char *actionText = (type == WIN_SCREENn) ? "Next" : "Restart";
    Color actionColor = (type == WIN_SCREENn) ? DARKGREEN : MAROON;
    DrawRectangle(actionX, actionY, btnW, btnH, actionColor);
    int actionTextW = MeasureText(actionText, btnH * 0.5f);
    DrawText(actionText, actionX + (btnW - actionTextW) / 2, actionY + (btnH - btnH * 0.5f) / 2,
             btnH * 0.5f, WHITE);
}


EndScreenResult HandleEndScreenInput(EndScreenType type) {
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();

    int winW = screenW * 0.7f;
    int winH = screenH * 0.7f;
    int winX = (screenW - winW) / 2;
    int winY = (screenH - winH) / 2;

    int btnW = screenW * 0.25f;
    int btnH = screenH * 0.1f;
    int mainMenuX = winX + winW / 4 - btnW / 2;
    int mainMenuY = winY + winH * 3 / 4;
    int actionX = winX + winW * 3 / 4 - btnW / 2;
    int actionY = mainMenuY;

    Vector2 inputPos;
    bool inputActive = false;
#if defined(PLATFORM_ANDROID) || defined(PLATFORM_WEB)
    if (GetTouchPointCount() > 0) {
        inputPos = GetTouchPosition(0);
        inputActive = true;
    }
#else
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        inputPos = GetMousePosition();
        inputActive = true;
    }
#endif

    EndScreenResult result = {};

    if (inputActive) {
        Rectangle mainMenuRect = {(float) mainMenuX, (float) mainMenuY, (float) btnW,
                                  (float) btnH};
        Rectangle actionRect = {(float) actionX, (float) actionY, (float) btnW, (float) btnH};
        if (CheckCollisionPointRec(inputPos, mainMenuRect)) result.mainMenuPressed = true;
        if (CheckCollisionPointRec(inputPos, actionRect)) result.actionPressed = true;
    }

    return result;
}


int main(void) {
    InitWindow(0, 0, "Treasure Hunt");
    InitAudioDevice();
    SetTargetFPS(60);

    // Load saved progress if it exists
    LoadGameProgress(coins, diamonds, level);
    bool s=false;
    Music main_bg,skateboard;
    Sound treas=LoadSound("treasure1.mp3");
    Sound pen=LoadSound("penalty2.mp3");
    Music nit=LoadMusicStream("nitro.mp3");
    // Load background texture
    Texture2D campusBg = LoadTexture("bg.png");
    Texture2D mapTexture = LoadTexture("hdmap.png");
    Texture2D playerTexture = LoadTexture("player.png");
    Texture2D Abscn,hp;
    // Initialize game state
    GameState currentState = MAIN_MENU;

    InitGame(GetScreenWidth(), GetScreenHeight());
    float elapsedTime = levels[level][2],timer=0;
    while (!WindowShouldClose()) {
        BeginDrawing();
        // State management using switch case
        switch (currentState) {
            case MAIN_MENU: {
                if(!s){
                    main_bg=LoadMusicStream("start2.mp3");
                    if(IsMusicValid(main_bg))PlayMusicStream(main_bg);
                    s=true;
                }
                if(IsMusicValid(main_bg))UpdateMusicStream(main_bg);
                // Draw background
                UpdateMusicStream(main_bg);
                DrawTexturePro(
                        campusBg,
                        (Rectangle) {0, 0, (float) campusBg.width, (float) campusBg.height},
                        (Rectangle) {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()},
                        (Vector2) {0, 0},
                        0.0f,
                        WHITE
                );
                // Draw starting window
                DrawStartingWindow();

                // Handle button presses
                ButtonAction action = HandleButtonPress();
                switch (action) {
                    case ABOUT_PRESSED:
                        currentState = ABOUT_SCREEN;
                        StopMusicStream(main_bg);
                        UnloadMusicStream(main_bg);
                        s=false;
                        break;
                    case HELP_PRESSED:
                        currentState = HELP_SCREEN;
                        StopMusicStream(main_bg);
                        UnloadMusicStream(main_bg);
                        s=false;
                        break;
                    case PLAY_PRESSED:
                        currentState = PLAY_SCREEN;
                        StopMusicStream(main_bg);
                        UnloadMusicStream(main_bg);
                        s=false;
                        break;
                    default:
                        break;
                }
                break;
            }

            case ABOUT_SCREEN: {
                if(!s){
                    Abscn=LoadTexture("about.png");
                    main_bg=LoadMusicStream("start.mp3");
                    if(IsMusicValid(main_bg))PlayMusicStream(main_bg);
                    s=true;
                }
                DrawTexturePro(Abscn,(Rectangle) {0, 0, (float) Abscn.width, (float) Abscn.height},(Rectangle) {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()},(Vector2) {0, 0},0.0f,WHITE);
                DrawTopRightButton();
                if(IsMusicValid(main_bg))UpdateMusicStream(main_bg);
                if (IsTopRightButtonPressed()) {
                    currentState = MAIN_MENU;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    UnloadTexture(Abscn);
                    s=false;
                }
                break;
            }

            case HELP_SCREEN: {
                DrawHelpScreen();
                if(!s){
                    hp=LoadTexture("help.png");
                    main_bg=LoadMusicStream("help2.mp3");
                    if(IsMusicValid(main_bg))PlayMusicStream(main_bg);
                    s=true;
                }
                DrawTexturePro(hp,(Rectangle) {0, 0, (float) hp.width, (float) hp.height},(Rectangle) {0, 0, (float) GetScreenWidth(), (float) GetScreenHeight()},(Vector2) {0, 0},0.0f,WHITE);
                DrawTopRightButton();
                if(IsMusicValid(main_bg))UpdateMusicStream(main_bg);
                if (IsTopRightButtonPressed()) {
                    UnloadTexture(hp);
                    currentState = MAIN_MENU;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    s=false;
                }
                break;
            }

            case PLAY_SCREEN: {
                int factor=1;
                if(!s){
                    main_bg=LoadMusicStream("play.mp3");
                    skateboard=LoadMusicStream("skateboard.mp3");
                    if(IsMusicValid(main_bg))PlayMusicStream(main_bg);
                    s=true;
                }
                if(IsMusicValid(main_bg))UpdateMusicStream(main_bg);
                elapsedTime -= GetFrameTime() * 0.7f;
                if (elapsedTime < 0) elapsedTime = 0;
                if(nitroOn){
                    if(IsMusicValid(nit))PlayMusicStream(nit);
                    factor=2;
                    timer-=GetFrameTime() * 0.7f;
                    if(timer<=0){
                        nitroOn=false;
                        StopMusicStream(nit);
                        timer=0;
                    }
                }
                DrawPlayScreen(nit,timer,factor,treas,pen, skateboard,playerTexture,mapTexture, elapsedTime);

                // Win condition
                if (treasures >= levels[level][0]) {
                    currentState = WIN_SCREEN;
                    if (level < (int) levels.size() - 1) level++;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    UnloadMusicStream(skateboard);
                    s=false;
                } else if (penalty >=levels[level][1] || elapsedTime <= 0.1f) {
                    currentState = GAME_OVER;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    UnloadMusicStream(skateboard);
                    s=false;
                }
                // Exit to main menu
                if (IsTopRightButtonPressed()) {
                    reset(elapsedTime);
                    currentState = MAIN_MENU;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    UnloadMusicStream(skateboard);
                    s=false;
                }
                break;
            }

            case WIN_SCREEN: {
                if(!s){
                    main_bg=LoadMusicStream("win.mp3");
                    if(IsMusicValid(main_bg))PlayMusicStream(main_bg);
                    s=true;
                }
                if(IsMusicValid(main_bg))UpdateMusicStream(main_bg);
                int c=0,ds=0;
                DrawEndScreenUI(WIN_SCREENn,c,ds);
                EndScreenResult endResult = HandleEndScreenInput(WIN_SCREENn);
                if (endResult.mainMenuPressed) {
                    reset(elapsedTime);
                    currentState = MAIN_MENU;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    s=false;
                    coins+=c;
                    diamonds+=ds;
                }
                if (endResult.actionPressed) {
                    reset(elapsedTime);
                    currentState = PLAY_SCREEN;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    s=false;
                    coins+=c;
                    diamonds+=ds;
                }
                break;
            }
            case GAME_OVER: {
                if(!s){
                    main_bg=LoadMusicStream("game_over.mp3");
                    if(IsMusicValid(main_bg))PlayMusicStream(main_bg);
                    s=true;
                }
                if(IsMusicValid(main_bg))UpdateMusicStream(main_bg);
                int c=0,ds=0;
                DrawEndScreenUI(GAME_OVER_SCREEN,c,ds);
                EndScreenResult endResult = HandleEndScreenInput(GAME_OVER_SCREEN);
                if (endResult.mainMenuPressed) {
                    reset(elapsedTime);
                    currentState = MAIN_MENU;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    s=false;
                    coins+=c;
                    diamonds+=ds;
                }
                if (endResult.actionPressed) {
                    reset(elapsedTime);
                    currentState = PLAY_SCREEN;
                    StopMusicStream(main_bg);
                    UnloadMusicStream(main_bg);
                    s=false;
                    coins+=c;
                    diamonds+=ds;
                }
                break;
            }
        }
        EndDrawing();
    }

    // Final save on exit
    SaveGameProgress(coins, diamonds, level);

    // Cleanup
    UnloadMusicStream(nit);
    UnloadSound(treas);
    UnloadSound(pen);
    UnloadTexture(mapTexture);
    UnloadTexture(campusBg);
    UnloadTexture(playerTexture);
    CloseWindow();
    return 0;
}
