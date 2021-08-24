#include <ilcplex/ilocplex.h>   /* cplex */    
#include <vector>              

namespace patch {template < typename T > std::string to_string( const T& n ){std::ostringstream stm; stm << n; return stm.str() ;}}

using namespace std;
////////////////////////////////////////////////////////
//                                                    //
// Source CPP Code for the CPLEX with Constraints (31)-(36) 
// Vessel Service Planning in Seaports, Operations Research
//                                                  
// Authors: Lingxiao Wu, Yossiri Adulyasak, Jean-Fran�ois Cordeau, Shuaian Wang 
///////////////////////////////////////////////////////

//input data starts here

extern const int S = 6;
extern const int K =10;
extern const int T = 288;
extern const int B = 10;
extern const int I = 20;
extern const int NCPN = 0;
extern const int HWPN = 180;
int BRT[B]={0,14,0,21,6,47,20,0,22,44};
int Chaocu[B]={-1,-1,-1,-1,-1,-1,-1,-1,-1,51};
int HDT[B]={-1,15,-1,22,7,48,21,-1,23,45};
int E[I][2]={{0,39},{0,28},{23,71},{29,77},{38,86},{62,110},{87,135},{93,141},{101,149},{140,188},{59,107},{71,119},{83,131},{145,193},{150,198},{133,181},{160,208},{161,209},{174,222},{216,264}};
int BRK[S][2]={{14,34},{62,82},{110,130},{158,178},{206,226},{254,274}};
int VLL[K]={0,0,0,2,1,1,0,0,0,0};
int F[I][I]={{0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0},{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1},{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0}};
int D[I+1]={7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6};
int H[K][B]={{52,52,52,52,52,52,52,52,52,52},{64,64,64,64,64,64,64,64,64,64},{53,53,53,53,53,53,53,53,53,53},{109,109,109,109,109,109,109,109,109,109},{105,105,105,105,105,105,105,105,105,105},{64,64,64,64,64,64,64,64,64,64},{66,66,66,66,66,66,66,66,66,66},{61,61,61,61,61,61,61,61,61,61},{66,66,66,66,66,66,66,66,66,66},{69,69,69,69,69,69,69,69,69,69}};
int Q[I+1][I+1]={{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
int ST[S][2]={{0,47},{48,95},{96,143},{144,191},{192,239},{240,287}};
int C1[K]={50000,50000,50000,50000,50000,50000,50000,50000,50000,50000};
int C2[I][T]={{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372,374,376,378,380,382,384,386,388,390,392,394,396,398,400,402,404,406,408,410,412,414,416,418,420,422,424,426,428,430,432,434,436,438,440,442,444,446,448,450,452,454,456,458,460,462,464,466,468,470,472,474,476,478,480,482,484,486,488,490,492,494,496,498,500,502,504,506,508,510,512,514,516,518,520,522,524,526,528,530,532,534,536,538,540,542,544,546,548,550,552,554,556,558,560,562,564,566,568,570,572,574},{0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372,374,376,378,380,382,384,386,388,390,392,394,396,398,400,402,404,406,408,410,412,414,416,418,420,422,424,426,428,430,432,434,436,438,440,442,444,446,448,450,452,454,456,458,460,462,464,466,468,470,472,474,476,478,480,482,484,486,488,490,492,494,496,498,500,502,504,506,508,510,512,514,516,518,520,522,524,526,528,530,532,534,536,538,540,542,544,546,548,550,552,554,556,558,560,562,564,566,568,570,572,574},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372,374,376,378,380,382,384,386,388,390,392,394,396,398,400,402,404,406,408,410,412,414,416,418,420,422,424,426,428,430,432,434,436,438,440,442,444,446,448,450,452,454,456,458,460,462,464,466,468,470,472,474,476,478,480,482,484,486,488,490,492,494,496,498,500,502,504,506,508,510,512,514,516,518,520,522,524,526,528},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102,108,114,120,126,132,138,144,150,156,162,168,174,180,186,192,198,204,210,216,222,228,234,240,246,252,258,264,270,276,282,288,294,300,306,312,318,324,330,336,342,348,354,360,366,372,378,384,390,396,402,408,414,420,426,432,438,444,450,456,462,468,474,480,486,492,498,504,510,516,522,528,534,540,546,552,558,564,570,576,582,588,594,600,606,612,618,624,630,636,642,648,654,660,666,672,678,684,690,696,702,708,714,720,726,732,738,744,750,756,762,768,774,780,786,792,798,804,810,816,822,828,834,840,846,852,858,864,870,876,882,888,894,900,906,912,918,924,930,936,942,948,954,960,966,972,978,984,990,996,1002,1008,1014,1020,1026,1032,1038,1044,1050,1056,1062,1068,1074,1080,1086,1092,1098,1104,1110,1116,1122,1128,1134,1140,1146,1152,1158,1164,1170,1176,1182,1188,1194,1200,1206,1212,1218,1224,1230,1236,1242,1248,1254,1260,1266,1272,1278,1284,1290,1296,1302,1308,1314,1320,1326,1332,1338,1344,1350,1356,1362,1368,1374,1380,1386,1392,1398,1404,1410,1416,1422,1428,1434,1440,1446,1452,1458,1464,1470,1476,1482,1488,1494,1500,1506,1512,1518,1524,1530,1536,1542,1548},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452,456,460,464,468,472,476,480,484,488,492,496,500,504,508,512,516,520,524,528,532,536,540,544,548,552,556,560,564,568,572,576,580,584,588,592,596,600,604,608,612,616,620,624,628,632,636,640,644,648,652,656,660,664,668,672,676,680,684,688,692,696,700,704,708,712,716,720,724,728,732,736,740,744,748,752,756,760,764,768,772,776,780,784,788,792,796,800,804,808,812,816,820,824,828,832,836,840,844,848,852,856,860,864,868,872,876,880,884,888,892,896,900,904,908,912,916,920,924,928,932,936,940,944,948,952,956,960,964,968,972,976,980,984,988,992,996},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,102,105,108,111,114,117,120,123,126,129,132,135,138,141,144,147,150,153,156,159,162,165,168,171,174,177,180,183,186,189,192,195,198,201,204,207,210,213,216,219,222,225,228,231,234,237,240,243,246,249,252,255,258,261,264,267,270,273,276,279,282,285,288,291,294,297,300,303,306,309,312,315,318,321,324,327,330,333,336,339,342,345,348,351,354,357,360,363,366,369,372,375,378,381,384,387,390,393,396,399,402,405,408,411,414,417,420,423,426,429,432,435,438,441,444,447,450,453,456,459,462,465,468,471,474,477,480,483,486,489,492,495,498,501,504,507,510,513,516,519,522,525,528,531,534,537,540,543,546,549,552,555,558,561,564,567,570,573,576,579,582,585,588,591,594,597,600,603,606,609,612,615,618,621,624,627,630,633,636,639,642,645,648,651,654,657,660,663,666,669,672,675},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372,374,376,378,380,382,384,386,388,390,392,394,396,398,400},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372,374,376,378,380,382,384,386,388},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294,296,298,300,302,304,306,308,310,312,314,316,318,320,322,324,326,328,330,332,334,336,338,340,342,344,346,348,350,352,354,356,358,360,362,364,366,368,370,372},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,202,204,206,208,210,212,214,216,218,220,222,224,226,228,230,232,234,236,238,240,242,244,246,248,250,252,254,256,258,260,262,264,266,268,270,272,274,276,278,280,282,284,286,288,290,292,294},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452,456,460,464,468,472,476,480,484,488,492,496,500,504,508,512,516,520,524,528,532,536,540,544,548,552,556,560,564,568,572,576,580,584,588,592,596,600,604,608,612,616,620,624,628,632,636,640,644,648,652,656,660,664,668,672,676,680,684,688,692,696,700,704,708,712,716,720,724,728,732,736,740,744,748,752,756,760,764,768,772,776,780,784,788,792,796,800,804,808,812,816,820,824,828,832,836,840,844,848,852,856,860,864,868,872,876,880,884,888,892,896,900,904,908,912},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452,456,460,464,468,472,476,480,484,488,492,496,500,504,508,512,516,520,524,528,532,536,540,544,548,552,556,560,564,568,572,576,580,584,588,592,596,600,604,608,612,616,620,624,628,632,636,640,644,648,652,656,660,664,668,672,676,680,684,688,692,696,700,704,708,712,716,720,724,728,732,736,740,744,748,752,756,760,764,768,772,776,780,784,788,792,796,800,804,808,812,816,820,824,828,832,836,840,844,848,852,856,860,864},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452,456,460,464,468,472,476,480,484,488,492,496,500,504,508,512,516,520,524,528,532,536,540,544,548,552,556,560,564,568,572,576,580,584,588,592,596,600,604,608,612,616,620,624,628,632,636,640,644,648,652,656,660,664,668,672,676,680,684,688,692,696,700,704,708,712,716,720,724,728,732,736,740,744,748,752,756,760,764,768,772,776,780,784,788,792,796,800,804,808,812,816},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,24,36,48,60,72,84,96,108,120,132,144,156,168,180,192,204,216,228,240,252,264,276,288,300,312,324,336,348,360,372,384,396,408,420,432,444,456,468,480,492,504,516,528,540,552,564,576,588,600,612,624,636,648,660,672,684,696,708,720,732,744,756,768,780,792,804,816,828,840,852,864,876,888,900,912,924,936,948,960,972,984,996,1008,1020,1032,1044,1056,1068,1080,1092,1104,1116,1128,1140,1152,1164,1176,1188,1200,1212,1224,1236,1248,1260,1272,1284,1296,1308,1320,1332,1344,1356,1368,1380,1392,1404,1416,1428,1440,1452,1464,1476,1488,1500,1512,1524,1536,1548,1560,1572,1584,1596,1608,1620,1632,1644,1656,1668,1680,1692,1704},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,248,256,264,272,280,288,296,304,312,320,328,336,344,352,360,368,376,384,392,400,408,416,424,432,440,448,456,464,472,480,488,496,504,512,520,528,536,544,552,560,568,576,584,592,600,608,616,624,632,640,648,656,664,672,680,688,696,704,712,720,728,736,744,752,760,768,776,784,792,800,808,816,824,832,840,848,856,864,872,880,888,896,904,912,920,928,936,944,952,960,968,976,984,992,1000,1008,1016,1024,1032,1040,1048,1056,1064,1072,1080,1088,1096},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,12,18,24,30,36,42,48,54,60,66,72,78,84,90,96,102,108,114,120,126,132,138,144,150,156,162,168,174,180,186,192,198,204,210,216,222,228,234,240,246,252,258,264,270,276,282,288,294,300,306,312,318,324,330,336,342,348,354,360,366,372,378,384,390,396,402,408,414,420,426,432,438,444,450,456,462,468,474,480,486,492,498,504,510,516,522,528,534,540,546,552,558,564,570,576,582,588,594,600,606,612,618,624,630,636,642,648,654,660,666,672,678,684,690,696,702,708,714,720,726,732,738,744,750,756,762,768,774,780,786,792,798,804,810,816,822,828,834,840,846,852,858,864,870,876,882,888,894,900,906,912,918,924},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452,456,460,464,468,472,476,480,484,488,492,496,500,504,508},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452,456,460,464,468,472,476,480,484,488,492,496,500,504},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284,288,292,296,300,304,308,312,316,320,324,328,332,336,340,344,348,352,356,360,364,368,372,376,380,384,388,392,396,400,404,408,412,416,420,424,428,432,436,440,444,448,452},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,12,16,20,24,28,32,36,40,44,48,52,56,60,64,68,72,76,80,84,88,92,96,100,104,108,112,116,120,124,128,132,136,140,144,148,152,156,160,164,168,172,176,180,184,188,192,196,200,204,208,212,216,220,224,228,232,236,240,244,248,252,256,260,264,268,272,276,280,284}};
int C3[K][B]={{330,260,309,356,382,302,263,348,354,333},{442,371,352,438,461,454,378,320,323,416},{337,310,352,371,334,299,315,268,376,305},{703,676,719,600,621,779,807,692,627,545},{557,698,693,588,662,761,704,557,588,751},{336,355,336,467,326,403,406,400,454,339},{429,469,399,393,403,333,416,403,416,379},{375,345,345,448,305,381,378,308,323,393},{330,439,469,393,353,360,442,406,406,347},{466,469,414,373,449,490,480,421,500,511}};
int C4[S]={48,48,48,48,48,48};
int ODS[2][1]={{},{}};
int Hset[2][HWPN]={{0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,19},{1,2,3,4,5,6,7,8,9,0,2,3,4,5,6,7,8,9,0,1,3,4,5,6,7,8,9,0,1,2,4,5,6,7,8,9,0,1,2,3,5,6,7,8,9,0,1,2,3,4,6,7,8,9,0,1,2,3,4,5,7,8,9,0,1,2,3,4,5,6,8,9,0,1,2,3,4,5,6,7,9,0,1,2,3,4,5,6,7,8,11,12,13,14,15,16,17,18,19,10,12,13,14,15,16,17,18,19,10,11,13,14,15,16,17,18,19,10,11,12,14,15,16,17,18,19,10,11,12,13,15,16,17,18,19,10,11,12,13,14,16,17,18,19,10,11,12,13,14,15,17,18,19,10,11,12,13,14,15,16,18,19,10,11,12,13,14,15,16,17,19,10,11,12,13,14,15,16,17,18}};

//input data ends here

extern const int P=S*I; //Number of pilots
extern const int J=P; //Number of rest periods
int pcounter=0;
int SPN[S];  
vector<vector<int>> SPS(S); 
int PN; 
vector<vector<int>> BTW(2);  
int PIN=0;
int PIindex[P][I+1]; 
int PIJN=0;
int PIJindex[P][I+1][I+1];
int SIN=0;
int SIindex[S][I]; 
int KBN=0;
int KBindex[K][B]; 
int ITN=0;
int ITindex[I+J][T]; 
int KTN=0;
int KTindex[K][T]; 
int KBTN=0;
int KBTindex[K][B][T]; 
int TSN[T]; 
vector<vector<int>> TSset(T);  
int BM[I][I]; 
int PIM[J][I]; 
int IPM[I][J]; 
int OVIT[I][T]; 
int Fout[K]; 
int Fin[K]; 
clock_t t_start,t_end;

void Cplexsetup () {
	for (int k=0;k!=K;++k){
		 int temp=T;
		 for (int b=0;b!=B;++b){
			 if (E[k][0]+H[k][b]+D[k]<temp){
			 temp=E[k][0]+H[k][b];
			 }
		 }
	     Fout[k]=temp;
	}
	for (int k=0;k!=K;++k){
		int temp=-T;
		for (int b=0;b!=B;++b){
			if (E[k+K][1]-D[K+k]-H[k][b]>temp){
				temp=E[k+K][1]-D[K+k]-H[k][b];
			}
		}
		Fin[k]=temp;
	}
	for (int i=0;i!=I;++i){
		for (int j=0;j!=I;++j){
			BM[i][j]=0;
			if (i==j){
				continue;
			}
			BM[i][j]=E[i][1]+D[i]+Q[i][j]-E[j][0];
			if(BM[i][j]<0){
				BM[i][j]=0;
			}
		}
	}
	for (int t=0;t!=T;++t){
		TSN[t]=0;
	}
	for (int s=0;s!=S;++s){
		for (int t=ST[s][0];t<=ST[s][1];++t){
			TSN[t]=+1;
			TSset[t].resize(TSN[t],s);
		}
	}
	PN=0;
	for (int s=0;s!=S;++s){
		SPN[s]=0;
	}
	for (int s=0;s!=S;++s){
		for (int i=0;i!=I;++i){
			int doable=1;
			if (E[i][1]<ST[s][0] || E[i][0]>ST[s][1]){
				doable=0;
			}
			if (doable==1){
				SPN[s]+=1; 
				SPS[s].resize(SPN[s],pcounter);
				PN+=1;
				pcounter+=1;
				BTW[0].resize(pcounter,BRK[s][0]);
				BTW[1].resize(pcounter,BRK[s][1]);
			}
		}
	}
	for (int p=0;p!=pcounter;++p){
		for (int i=0;i!=I+1;++i){
			PIindex[p][i]=PIN;
			PIN+=1;
		}
	}
	for (int p=0;p!=pcounter;++p){
		for (int i=0;i!=I+1;++i){
			for (int j=0;j!=I+1;++j){
				if (i==j){continue;}
				PIJindex[p][i][j]=PIJN;
				PIJN+=1;
			}
		}
	}
	for (int s=0;s!=S;++s){
			for (int i=0;i!=I;++i){
				SIindex[s][i]=SIN;
				SIN+=1;
			}
	}
	for (int i=0;i!=I+pcounter;++i){
		for (int t=0;t!=T;++t){
			ITindex[i][t]=ITN;
			ITN+=1;
		}
	}
	for (int k=0;k!=K;++k){
		for (int b=0;b!=B;++b){
			KBindex[k][b]=KBN;
			KBN+=1;
		}
	}
	for (int k=0;k!=K;++k){
		for (int t=0;t!=T;++t){
			KTindex[k][t]=KTN;
			KTN+=1;
		}
	}
	for (int k=0;k!=K;++k){
		for (int b=0;b!=B;++b){
			for (int t=0;t!=T;++t){
				KBTindex[k][b][t]=KBTN;
				KBTN+=1;
			}
		}
	}
	for(int i=0;i!=I;++i){
		for (int p=0;p!=pcounter;++p){
			IPM[i][p]=E[i][1]+D[i]+Q[i][I];
			if (IPM[i][p]<0){
				IPM[i][p]=0;
			}
			PIM[p][i]=BTW[1][p]+D[I]+Q[I][i]-E[i][0];
			if (PIM[p][i]<0){
				PIM[p][i]=0;
			}
		}
	}
		for (int i=0;i!=I;++i){
		for (int t=E[i][0];t<=E[i][1];++t){
			OVIT[i][t]=1;
		}
	}    
	for (int i=K;i!=2*K;++i){
		for (int b=0;b!=B;++b){
			int timet=BRT[b];
			int edtime=HDT[b];
			if (HDT[b]!=-1){
				for (int tt=timet;tt<edtime;++tt){
					OVIT[i][tt]=0;}}
		}
	}
	for (int i=0;i!=K;++i){
		if (VLL[i]>=2){
			for (int b=0;b!=B;++b){
				int time02=Chaocu[b];
				if (time02!=-1){
					int timet=BRT[b];
					for (int t=timet;t<=time02-1;++t){
						OVIT[i][t]=0;
					}
				}
			}
		}
	}
	for (int i=0;i!=I;++i){
		for (int t=E[i][0];t<=E[i][1];++t){
			int doable=0;
			for (int n=0;n!=TSN[t];++n){
				int thes=TSset[t][n];
				if (BRK[thes][0]+D[I]<=t){
					doable=1;
				    break;
				}
				if (t+D[i]<=BRK[thes][1]){
					doable=1;
					break;
				}
			}
			OVIT[i][t]=doable;
		}
	}
}

void inputData () {
	Cplexsetup ();
}

void BAPPPP () {
	ILOSTLBEGIN
	IloEnv env;
	IloNumVar obj(env, -IloInfinity, IloInfinity, ILOFLOAT);
	IloNumVarArray u(env, KBN, 0, 1, ILOINT); 
	IloNumVarArray vin(env, KTN, 0, 1, ILOINT);
	IloNumVarArray vout(env, KTN, 0, 1, ILOINT);
	IloNumVarArray w(env, KBTN, 0, 1, ILOINT);
	IloNumVarArray x(env,  ITN, 0, 1, ILOINT);
	IloNumVarArray oy(env, PIN, 0, 1, ILOINT);  
	IloNumVarArray ty(env, PIN, 0, 1, ILOINT);  
	IloNumVarArray y(env,  PIJN, 0, 1, ILOINT);  
	IloNumVarArray z(env,  SIN, 0, 1, ILOINT); 
	IloNumVarArray n(env,  S, 0, IloInfinity, ILOINT);
	try{
		///// define indices /////
		IloInt p,k,k1,k2,b,b1,t,t1,s,r,g,i,j;   
		///// create model ///// 
		IloModel model(env);
		///// add constraints /////
		{ 
			model.add(IloMinimize(env, obj));
		} 
		{   
			IloExpr Z2(env); 
			IloExpr Z3(env); 
			IloExpr Z4(env); 
			for (i=0;i!=I;++i){
				for (t=E[i][0];t<=E[i][1];++t){
					Z2+=C2[i][t]*x[ITindex[i][t]];
				}
			}
			for (k=0;k!=K;++k){
				for (b=0;b!=B;++b){
					Z3+=C3[k][b]*u[KBindex[k][b]];
				}
			}
			for (s=0;s!=S;++s){
				Z4+=C4[s]*n[s];
			}
			model.add(obj==Z2+Z3+Z4);
			Z2.end();
			Z3.end();
			Z4.end();
		}
		{   
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				for (b=0;b!=B;++b){
				sum1+=u[KBindex[k][b]];
				}
				model.add(sum1==1); 
				sum1.end();
			}
		}
		{   
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				for (t=0;t!=T;++t){
					sum1+=vin[KTindex[k][t]];
				}
				model.add(sum1==1); 
				sum1.end();
			}
		}
		{    
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				for (t=0;t!=T;++t){
					sum1+=vout[KTindex[k][t]];
				}
				model.add(sum1==1); 
				sum1.end();
			}
		}
		{ 
			for (k=0;k!=K;++k){
			     IloExpr sum1(env);
				 IloExpr sum2(env);
				 for (t=0;t!=T;++t){
					 sum1+=t*vin[KTindex[k][t]];
				 }
				 for (b=0;b!=B;++b){
					 sum2+=BRT[b]*u[KBindex[k][b]];
				 }
				 model.add(sum1>=sum2);
				 sum1.end();
				 sum2.end();
			}
		}
		{ 
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				IloExpr sum2(env);
				IloExpr sum3(env);
				for (t=0;t!=T;++t){
					sum1+=t*vout[KTindex[k][t]];
				}
				for (t=0;t!=T;++t){
					sum2+=t*vin[KTindex[k][t]];
				}
				for (b=0;b!=B;++b){
					sum3+=H[k][b]*u[KBindex[k][b]];
				}
				model.add(sum1>=sum2+sum3);
				sum1.end();
				sum2.end();
				sum3.end();
			}
		}
		{  
			for (k=0;k!=K;++k){
				for (b=0;b!=B;++b){
					for (t=0;t!=T;++t){
					IloExpr sum1(env);
					IloExpr sum2(env);
					for (t1=0;t1<=t;++t1){
						sum1+=vin[KTindex[k][t1]];
					}
					for (t1=t+1;t1<T;++t1){
						sum2+=vout[KTindex[k][t1]];
					}
					model.add(w[KBTindex[k][b][t]]>=u[KBindex[k][b]]+sum1+sum2-2);
					sum1.end();
					sum2.end();
				}
			}
			}
		}
		{  
			for (b=0;b!=B;++b){
				for (t=0;t!=T;++t){
				IloExpr sum1(env);
				for (k=0;k!=K;++k){
					sum1+=w[KBTindex[k][b][t]];}
				model.add(sum1<=1);
				sum1.end();
				}
			}
		}
		{  
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				for (t=E[k][0];t<=E[k][1];++t){
					if (OVIT[k][t]==0){model.add(x[ITindex[k][t]]==0);}
					sum1+=x[ITindex[k][t]];
				}
				model.add(sum1==1); 
				sum1.end();
			}
		}
		{  
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				for (t=E[k+K][0];t<=E[k+K][1];++t){
					if (OVIT[k+K][t]==0){model.add(x[ITindex[k+K][t]]==0);}
						sum1+=x[ITindex[k+K][t]];
				}
				model.add(sum1==1); 
				sum1.end();
			}
		}
		{ 
			for (g=0;g!=HWPN;++g){
				for (t1=0;t1!=T;++t1){
					i=Hset[0][g];
					j=Hset[1][g];
					IloExpr sum1(env);
					int st1=t1-F[i][j]+1;
					if (st1<E[i][0]){st1=E[i][0];}
					int et1=t1;
					if (et1>E[i][1]){et1=E[i][1];}
					for (t=st1;t<=et1;++t){
						sum1+=x[ITindex[i][t]];
					}
					if (t1>=E[j][0] && t1<=E[j][1]){
						sum1+=x[ITindex[j][t1]];
					}
					model.add(sum1<=1);
					sum1.end();
				}
			}
		}
		{ 
			for (g=0;g!=NCPN;++g){
				for (t1=0;t1!=T;++t1){
					i=ODS[0][g];
					j=ODS[1][g];
					IloExpr sum1(env);
					int st1=t1-D[i]+1;
					if (st1<E[i][0]){st1=E[i][0];}
					int et1=t1;
					if (et1>E[i][1]){et1=E[i][1];}
					for (t=st1;t<=et1;++t){
						sum1+=x[ITindex[i][t]];
					}
					int st2=t1-D[i]+1;
					if (st2<E[j][0]){st2=E[j][0];}
					int et2=t1;
					if (et2>E[j][1]){et2=E[j][1];}
					for (t=st2;t<=et2;++t){
						sum1+=x[ITindex[j][t]];
					}
					model.add(sum1<=1);
					sum1.end();
				}
			}
		}
		{  
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				IloExpr sum2(env);
				for (t=E[k][0];t<=E[k][1];++t){
					sum1+=t*x[ITindex[k][t]];}
				for (t=0;t!=T;++t){
					sum2+=t*vin[KTindex[k][t]];
				}
				model.add(sum2==sum1+D[k]); 
				sum1.end();
				sum2.end();
			}
		}
		{  
			for (k=0;k!=K;++k){
				IloExpr sum1(env);
				IloExpr sum2(env);
				for (t=E[k+K][0];t<=E[k+K][1];++t){
					sum2+=t*x[ITindex[K+k][t]];}
				for (t=0;t!=T;++t){
					sum1+=t*vout[KTindex[k][t]];
				}
				model.add(sum2==sum1); 
				sum1.end();
				sum2.end();
			}
		}
		{  
			for (p=0;p!=pcounter;++p){
				IloExpr sum1(env);
				for (j=0;j!=I+1;++j){
					sum1+=oy[PIindex[p][j]];
				}
				model.add(sum1<=1);
				sum1.end();
			}
		}
		{  
			for (p=0;p!=pcounter;++p){
				for (j=0;j!=I+1;++j){
					IloExpr sum1(env);
					IloExpr sum2(env);
					sum1+=oy[PIindex[p][j]];
					for (i=0;i!=I+1;++i){
						if (i==j){continue;}
						sum1+=y[PIJindex[p][i][j]];
					}
					sum2+=ty[PIindex[p][j]];
					for (i=0;i!=I+1;++i){
						if (i==j){continue;}
						sum2+=y[PIJindex[p][j][i]];
					}
					model.add(sum1==sum2);
					sum1.end();
					sum2.end();
				}
			}
		}
		{  
			for (p=0;p!=pcounter;++p){
				IloExpr sum1(env);
				IloExpr sum2(env);
				for (j=0;j!=I+1;++j){
					sum1+=oy[PIindex[p][j]];
					sum2+=ty[PIindex[p][j]];	
				}
				model.add(sum1==sum2);
				sum1.end();
				sum2.end();
			}
		}
		{ 
			for (s=0;s!=S;++s){
					for (j=0;j!=I;++j){
						IloExpr sum1(env);
						for (int nn=0;nn!=SPN[s];++nn){
							p=SPS[s][nn];
							sum1+=oy[PIindex[p][j]];
							for (i=0;i!=I+1;++i){
								if (i==j){continue;}
								sum1+=y[PIJindex[p][i][j]];
							}
						}
						model.add(sum1==z[SIindex[s][j]]);
						sum1.end();
					}
			}
		}
		{ 
			for (i=0;i!=I;++i){
				for (t=E[i][0];t<=E[i][1];++t){
					IloExpr sum1(env);
					for (int n=0;n!=TSN[t];++n){
						s=TSset[t][n];
						sum1+=z[SIindex[s][i]];
					}
					model.add(x[ITindex[i][t]]<=sum1);
					sum1.end();
				}
			}
		}
		{ 
			for (p=0;p!=pcounter;++p){
				j=I+p;
				IloExpr sum1(env);
				IloExpr sum2(env);
				for (t=BTW[0][p];t<=BTW[1][p];++t){
					sum1+=x[ITindex[j][t]];
				}
				for (i=0;i!=I+1;++i){
					sum2+=oy[PIindex[p][i]];}
				model.add(sum1==sum2);
				sum1.end();
				sum2.end();
			}
		}
		{ 
			for (p=0;p!=pcounter;++p){
				IloExpr sum1(env);
				IloExpr sum2(env);
				sum1+=oy[PIindex[p][I]];
				for (i=0;i!=I;++i){
					sum1+=y[PIJindex[p][i][I]];
				}
				for (i=0;i!=I+1;++i){
					sum2+=oy[PIindex[p][i]];}
				model.add(sum1==sum2);
				sum1.end();
				sum2.end();
			}
		}
		{ 
			for (p=0;p!=pcounter;++p){
				for (i=0;i!=I;++i){
					for (j=0;j!=I;++j){
						if (i==j){continue;}
						IloExpr sum1(env);
						IloExpr sum2(env);
						for (t=E[i][0];t<=E[i][1];++t){
								sum1+=t*x[ITindex[i][t]];
						}
						for (t=E[j][0];t<=E[j][1];++t){
								sum2+=t*x[ITindex[j][t]];
							}
						model.add(sum2>=sum1+D[i]+Q[i][j]+BM[i][j]*(y[PIJindex[p][i][j]]-1));
						sum1.end();
						sum2.end();
				}
			}
			}
		}
		{ 
			for (p=0;p!=pcounter;++p){
				for (i=0;i!=I;++i){
					IloExpr sum1(env);
					IloExpr sum2(env);
					for (t=E[i][0];t<=E[i][1];++t){
						sum1+=t*x[ITindex[i][t]];}
					int thej=I+p;
					for (t=BTW[0][p];t<=BTW[1][p];++t){
						sum2+=t*x[ITindex[thej][t]];}
					model.add(sum2>=sum1+D[i]+Q[i][I]+IPM[i][p]*(y[PIJindex[p][i][I]]-1));
					model.add(sum1>=sum2+D[I]+Q[I][i]+PIM[p][i]*(y[PIJindex[p][I][i]]-1));
					sum1.end();
					sum2.end();
				}
			}
		}
		{ 
			for (p=0;p!=pcounter;++p){
				for (i=0;i!=I;++i){
					for (j=0;j!=I;++j){
						if (i==j){continue;}
						IloExpr sum1(env);
						IloExpr sum2(env);
						for (t=E[i][0];t<=E[i][1];++t){
							sum1+=t*x[ITindex[i][t]];
						}
						for (t=E[j][0];t<=E[j][1];++t){
							sum2+=t*x[ITindex[j][t]];
						}
						model.add(sum2>=sum1+D[i]+Q[i][j]+BM[i][j]*(y[PIJindex[p][i][I]]+y[PIJindex[p][I][j]]-2));
						sum1.end();
						sum2.end();
					}
				}
			}
		}
		{  
			for (s=0;s!=S;++s){
				IloExpr sum1(env);
				for (int nn=0;nn!=SPN[s];++nn){
					p=SPS[s][nn];
					for (i=0;i!=I+1;++i){
						sum1+=oy[PIindex[p][i]];}
				}
				model.add(n[s]==sum1);
				sum1.end();
			}
		}
		{  
			for (k=0;k!=K;++k){
				for (t=Fin[k]+1;t<=E[k][1];++t){
					model.add(x[ITindex[k][t]]==0);
				}
				for (t=E[k+K][0];t<=Fout[k]-1;++t){
					model.add(x[ITindex[k+K][t]]==0);
				}
			}
		}
		{  
			for (int i=0;i!=I;++i){
				for (int s=0;s!=S;++s){
				     int st=E[i][0];
					 if (st<ST[s][0]){
						 st=ST[s][0];
					 }
					 int et=E[i][1];
					 if (et>ST[s][1]){
					     et=ST[s][1];
					 }
					 IloExpr sum1(env);
					 IloExpr sum2(env);
					 for (t=st;t<=et;++t){
						 sum1+=x[ITindex[i][t]];
					 }
					 sum2+=z[SIindex[s][i]]; 
					 model.add(sum2<=sum1);
					 sum1.end();
					 sum2.end();
				}
			}
		}
		{
			for (s=0;s!=S;++s){
					for (int nn=0;nn<SPN[s]-1;++nn){
						IloExpr sum1(env);
						IloExpr sum2(env);
						int p1=SPS[s][nn];
						int p2=SPS[s][nn+1];
						for (i=0;i!=I+1;++i){
							sum1+=oy[PIindex[p1][i]];
							sum2+=oy[PIindex[p2][i]];
						}						 
						model.add(sum1>=sum2);
						sum1.end();
						sum2.end();
					}
			}
		}
		{ 
			for (s=0;s!=S;++s){
					for (int nn=0;nn<SPN[s]-1;++nn){
						int p1=SPS[s][nn];
						int p2=SPS[s][nn+1];
						for (i=0;i!=I;++i){
							IloExpr sum1(env);
							IloExpr sum2(env);
							for (j=0;j<=i;++j){
								IloExpr sum(env);
								double thecon=pow(2,double(i-j));
								sum+=oy[PIindex[p1][j]];
								for (int ii=0;ii!=I+1;++ii){
									if (ii==int(j)){continue;}
									sum+=y[PIJindex[p1][ii][j]];
								}
								sum1+=sum*thecon;
								sum.end();
							}
							for (j=0;j<=i;++j){
								IloExpr sum(env);
								double thecon=pow(2,double(i-j));
								sum+=oy[PIindex[p2][j]];
								for (int ii=0;ii!=I+1;++ii){
									if (ii==int(j)){continue;}
									sum+=y[PIJindex[p2][ii][j]];
								}
								sum2+=sum*thecon;
								sum.end();
							}
							model.add(sum1>=sum2);
							sum1.end();
							sum2.end();
						}
					}
			}
		}
		{
			IloCplex cplex(env);
			cplex.setParam(IloCplex::Param::TimeLimit,3600.0);
			cplex.extract(model);
			cplex.setParam(IloCplex::Threads, 6); 
			cplex.solve();
		    cout<<"The gap is"<<cplex.getMIPRelativeGap()*100<<endl;
			int thecost=ceil(cplex.getObjValue()-0.01);
			cout<<"The result is"<<thecost<<endl;
		}
		
	}
	catch(IloException& ex){
		cerr << ex << endl;
	}
	catch(...){
		cerr << "Error..." << endl;
	}
	env.end();
}

int main (int argc, char **argv) {
	t_start=clock();
	inputData();
	cout << "formulation" << endl;
    BAPPPP ();
	t_end =clock();
	cout << "time=" <<double(t_end-t_start)/1000<<endl;
	cout << "succeeded" << endl;
	return 0;
}
