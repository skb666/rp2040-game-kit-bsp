from math import ceil

from sqlalchemy import false


tones = {
    'C0':16, 'C#0':17, 'D0':18, 'D#0':19, 'E0':21, 'F0':22, 'F#0':23,
    'G0':24, 'G#0':26, 'A0':28, 'A#0':29, 'B0':31, 'C1':33, 'C#1':35,
    'D1':37, 'D#1':39, 'E1':41, 'F1':44, 'F#1':46, 'G1':49, 'G#1':52,
    'A1':55, 'A#1':58, 'B1':62, 'C2':65, 'C#2':69, 'D2':73, 'D#2':78,
    'E2':82, 'F2':87, 'F#2':92, 'G2':98, 'G#2':104, 'A2':110, 'A#2':117,
    'B2':123, 'C3':131, 'C#3':139, 'D3':147, 'D#3':156, 'E3':165, 'F3':175,
    'F#3':185, 'G3':196, 'G#3':208, 'A3':220, 'A#3':233, 'B3':247, 'C4':262,
    'C#4':277, 'D4':294, 'D#4':311, 'E4':330, 'F4':349, 'F#4':370, 'G4':392,
    'G#4':415, 'A4':440, 'A#4':466, 'B4':494, 'C5':523, 'C#5':554, 'D5':587,
    'D#5':622, 'E5':659, 'F5':698, 'F#5':740, 'G5':784, 'G#5':831, 'A5':880,
    'A#5':932, 'B5':988, 'C6':1047, 'C#6':1109, 'D6':1175, 'D#6':1245, 'E6':1319,
    'F6':1397, 'F#6':1480, 'G6':1568, 'G#6':1661, 'A6':1760, 'A#6':1865, 'B6':1976,
    'C7':2093, 'C#7':2217, 'D7':2349, 'D#7':2489, 'E7':2637, 'F7':2794, 'F#7':2960,
    'G7':3136, 'G#7':3322, 'A7':3520, 'A#7':3729, 'B7':3951, 'C8':4186, 'C#8':4435,
    'D8':4699, 'D#8':4978, 'E8':5274, 'F8':5588, 'F#8':5920, 'G8':6272, 'G#8':6645,
    'A8':7040, 'A#8':7459, 'B8':7902, 'C9':8372, 'C#9':8870, 'D9':9397, 'D#9':9956,
    'E9':10548, 'F9':11175, 'F#9':11840, 'G9':12544, 'G#9':13290, 'A9':14080, 'A#9':14917,
    'B9':15804
}

song = "0 A#4 1 1;2 F5 1 1;4 D#5 1 1;8 D5 1 1;11 D5 1 1;6 A#4 1 1;14 D#5 1 1;18 A#4 1 1;20 D#5 1 1;22 A#4 1 1;24 D5 1 1;27 D5 1 1;30 D#5 1 1;32 A#4 1 1;34 F5 1 1;36 D#5 1 1;38 A#4 1 1;40 D5 1 1;43 D5 1 1;46 D#5 1 1;50 A#4 1 1;52 D#5 1 1;54 G5 1 1;56 F5 1 1;59 D#5 1 1;62 F5 1 1;64 A#4 1 1;66 F5 1 1;68 D#5 1 1;70 A#4 1 1;72 D5 1 1;75 D5 1 1;78 D#5 1 1;82 A#4 1 1;84 D#5 1 1;86 A#4 1 1;88 D5 1 1;91 D5 1 1;94 D#5 1 1;96 A#4 1 1;100 D#5 1 1;102 A#4 1 1;104 D5 1 1;107 D5 1 1;110 D#5 1 1;114 A#4 1 1;116 D#5 1 1;118 G5 1 1;120 F5 1 1;123 D#5 1 1;126 F5 1 1;98 F5 1 1"
song1 = "0 D#5 4 43;0 D#7 4 43;0 D#6 4 43;4 F5 4 43;4 F7 4 43;4 F6 4 43;8 G5 4 43;8 G7 4 43;8 G6 4 43;12 F5 4 43;12 F7 4 43;12 F6 4 43;16 D#5 4 43;16 D#7 4 43;16 D#6 4 43;20 C5 4 43;20 C7 4 43;20 C6 4 43;24 D7 4 43;24 D5 4 43;24 D6 4 43;28 C7 4 43;28 C6 4 43;28 C5 4 43;32 G6 4 43;32 G4 4 43;32 G5 4 43;36 A#4 24 43;36 A#6 24 43;36 A#5 24 43;60 D#5 4 43;60 D#7 4 43;60 D#6 4 43;64 F5 4 43;64 F7 4 43;64 F6 4 43;68 G5 4 43;68 G7 4 43;68 G6 4 43;72 F5 4 43;72 F7 4 43;72 F6 4 43;76 D#5 4 43;76 D#7 4 43;76 D#6 4 43;80 C5 4 43;80 C7 4 43;80 C6 4 43;84 D7 4 43;84 D5 4 43;84 D6 4 43;88 A#6 4 43;88 A#4 4 43;88 A#5 4 43;92 G6 4 43;92 G4 4 43;92 G5 4 43;96 C5 24 43;96 C7 24 43;96 C6 24 43;120 A#4 4 43;120 A#6 4 43;120 A#5 4 43;124 G#4 4 43;124 G#6 4 43;124 G#5 4 43;128 G4 4 43;128 G6 4 43;128 G5 4 43;132 F4 12 43;132 F6 12 43;132 F5 12 43;144 D4 4 43;144 D6 4 43;144 D5 4 43;148 C4 4 43;148 C6 4 43;148 C5 4 43;152 A#3 4 43;152 A#5 4 43;152 A#4 4 43;156 G4 12 43;156 G6 12 43;156 G5 12 43;168 G#4 12 43;168 G#6 12 43;168 G#5 12 43;180 F4 8 43;180 F6 8 43;180 F5 8 43;188 D#4 4 43;188 D#6 4 43;188 D#5 4 43;192 D#4 24 43;192 D#6 24 43;192 D#5 24 43;216 A#5 4 43;220 C6 4 43;224 A#5 4 43;228 G#5 4 43;232 G5 4 43;236 F5 4 43;240 D#5 12 43;252 A#4 12 43;264 D#5 4 43;268 G5 4 43;272 D#6 4 43;276 D6 4 43;280 C6 6 43;286 G5 2 43;288 A#5 24 43;312 C6 4 43;316 D6 4 43;320 C6 4 43;324 A#5 4 43;328 G#5 4 43;332 G5 4 43;336 F5 12 43;348 C5 12 43;360 D5 4 43;364 C5 4 43;368 A#4 4 43;372 A#5 4 43;376 D#5 6 43;382 F5 2 43;384 G5 24 43;408 A#5 4 43;412 C6 4 43;416 A#5 4 43;420 G#5 4 43;424 G5 4 43;428 F5 4 43;432 D#5 12 43;444 A#4 12 43;456 D#5 4 43;460 G5 4 43;464 D#6 4 43;468 D6 4 43;472 F6 6 43;478 D#6 2 43;480 C6 24 43;504 D#6 4 43;508 D6 4 43;512 C6 4 43;516 A#5 12 43;528 C6 4 43;532 A#5 4 43;536 G#5 4 43;540 G5 12 43;552 D5 8 43;560 C5 4 43;564 A#4 8 43;572 F5 4 43;576 D#5 24 43;600 A#5 4 43;604 C6 4 43;608 A#5 4 43;612 G#5 4 43;616 G5 4 43;620 F5 4 43;624 D#5 12 43;636 A#4 12 43;648 D#5 4 43;652 G5 4 43;656 D#6 4 43;660 D6 4 43;664 C6 6 43;670 G5 2 43;672 A#5 24 43;696 C6 4 43;700 D6 4 43;704 C6 4 43;708 A#5 4 43;712 G#5 4 43;716 G5 4 43;720 F5 12 43;732 C5 12 43;744 D5 4 43;748 C5 4 43;752 A#4 4 43;756 A#5 4 43;760 D#5 6 43;766 F5 2 43;768 G5 24 43;792 A#5 4 43;796 C6 4 43;800 A#5 4 43;804 G#5 4 43;808 G5 4 43;812 F5 4 43;816 D#5 12 43;828 A#4 12 43;840 D#5 4 43;844 G5 4 43;848 D#6 4 43;852 D6 4 43;856 F6 6 43;862 D#6 2 43;864 C6 24 43;888 D#6 4 43;892 D6 4 43;896 C6 4 43;900 A#5 12 43;912 C6 4 43;916 A#5 4 43;920 G#5 4 43;924 G5 12 43;936 D5 8 43;944 C5 4 43;948 A#4 8 43;956 F5 4 43;960 D#5 24 43;984 D#6 4 43;988 F6 4 43;992 G6 4 43;996 F6 4 43;1000 D#6 4 43;1004 C6 4 43;1008 D6 4 43;1012 A#5 4 43;1016 G5 4 43;1020 A#5 24 43;1044 D#6 4 43;1048 F6 4 43;1052 G6 4 43;1056 F6 4 43;1060 D#6 4 43;1064 C6 4 43;1068 D6 4 43;1072 A#5 4 43;1076 G5 4 43;1080 C6 24 43;1104 A#5 4 43;1108 G#5 4 43;1112 G5 4 43;1116 F5 12 43;1128 D5 4 43;1132 C5 4 43;1136 A#4 4 43;1140 G5 12 43;1152 G#5 12 43;1164 F5 8 43;1172 D#5 4 43;1176 D#5 24 43;1200 A#5 4 43;1204 C6 4 43;1208 A#5 4 43;1212 G#5 4 43;1216 G5 4 43;1220 F5 4 43;1224 D#5 12 43;1236 A#4 12 43;1248 D#5 4 43;1252 G5 4 43;1256 D#6 4 43;1260 D6 4 43;1264 C6 6 43;1270 G5 2 43;1272 A#5 24 43;1296 C6 4 43;1300 D6 4 43;1304 C6 4 43;1308 A#5 4 43;1312 G#5 4 43;1316 G5 4 43;1320 F5 12 43;1332 C5 12 43;1344 D5 4 43;1348 C5 4 43;1352 A#4 4 43;1356 A#5 4 43;1360 D#5 6 43;1366 F5 2 43;1368 G5 24 43;1392 A#5 4 43;1396 C6 4 43;1400 A#5 4 43;1404 G#5 4 43;1408 G5 4 43;1412 F5 4 43;1416 D#5 12 43;1428 A#4 12 43;1440 D#5 4 43;1444 G5 4 43;1448 D#6 4 43;1452 D6 4 43;1456 F6 6 43;1462 D#6 2 43;1464 C6 24 43;1488 D#6 4 43;1492 D6 4 43;1496 C6 4 43;1500 A#5 12 43;1512 C6 4 43;1516 A#5 4 43;1520 G#5 4 43;1524 G5 12 43;1536 D5 8 43;1544 C5 4 43;1548 A#4 8 43;1556 F5 4 43;1560 D#5 24 43;1584 D#6 4 43;1588 F6 4 43;1592 G6 4 43;1596 F6 4 43;1600 D#6 4 43;1604 C6 4 43;1608 D6 4 43;1612 A#5 4 43;1616 G5 4 43;1620 A#5 24 43;1644 D#6 4 43;1648 F6 4 43;1652 G6 4 43;1656 F6 4 43;1660 D#6 4 43;1664 C6 4 43;1668 D6 4 43;1672 A#5 4 43;1676 G5 4 43;1680 C6 24 43;1704 A#5 4 43;1708 G#5 4 43;1712 G5 4 43;1716 F5 12 43;1728 D5 4 43;1732 C5 4 43;1736 A#4 4 43;1740 G5 12 43;1752 G#5 12 43;1764 F5 8 43;1772 D#5 4 43;1776 D#5 24 43;1800 D#5 4 43;1800 D#7 4 43;1800 D#6 4 43;1804 F5 4 43;1804 F7 4 43;1804 F6 4 43;1808 G5 4 43;1808 G7 4 43;1808 G6 4 43;1812 F5 4 43;1812 F7 4 43;1812 F6 4 43;1816 D#5 4 43;1816 D#7 4 43;1816 D#6 4 43;1820 C5 4 43;1820 C7 4 43;1820 C6 4 43;1824 D7 4 43;1824 D5 4 43;1824 D6 4 43;1828 C7 4 43;1828 C5 4 43;1828 C6 4 43;1832 G6 4 43;1832 G4 4 43;1832 G5 4 43;1836 A#4 24 43;1836 A#6 24 43;1836 A#5 24 43;1860 D#5 4 43;1860 D#7 4 43;1860 D#6 4 43;1864 F5 4 43;1864 F7 4 43;1864 F6 4 43;1868 G5 4 43;1868 G7 4 43;1868 G6 4 43;1872 F5 4 43;1872 F7 4 43;1872 F6 4 43;1876 D#5 4 43;1876 D#7 4 43;1876 D#6 4 43;1880 C5 4 43;1880 C7 4 43;1880 C6 4 43;1884 D7 4 43;1884 D5 4 43;1884 D6 4 43;1888 A#6 4 43;1888 A#4 4 43;1888 A#5 4 43;1892 G6 4 43;1892 G4 4 43;1892 G5 4 43;1896 C5 24 43;1896 C7 24 43;1896 C6 24 43;1920 A#4 4 43;1920 A#6 4 43;1920 A#5 4 43;1924 G#4 4 43;1924 G#6 4 43;1924 G#5 4 43;1928 G4 4 43;1928 G6 4 43;1928 G5 4 43;1932 F4 12 43;1932 F6 12 43;1932 F5 12 43;1944 D4 4 43;1944 D6 4 43;1944 D5 4 43;1948 C4 4 43;1948 C6 4 43;1948 C5 4 43;1952 A#3 4 43;1952 A#5 4 43;1952 A#4 4 43;1956 G4 12 43;1956 G6 12 43;1956 G5 12 43;1992 D#6 36 43"
song2 = "0 B5 1 0;2 A5 1 0;4 G#5 1 0;6 A5 1 0;8 C6 1 0;16 D6 1 0;18 C6 1 0;20 B5 1 0;22 C6 1 0;24 E6 1 0;32 F6 1 0;34 E6 1 0;36 D#6 1 0;38 E6 1 0;8 A3 1 0;12 C4 1 0;12 E4 1 0;16 C4 1 0;16 E4 1 0;20 C4 1 0;20 E4 1 0;24 A3 1 0;28 C4 1 0;28 E4 1 0;32 C4 1 0;32 E4 1 0;36 C4 1 0;36 E4 1 0;40 A3 1 0;44 C4 1 0;44 E4 1 0;48 A3 1 0;52 C4 1 0;52 E4 1 0;40 B6 1 0;42 A6 1 0;44 G#6 1 0;46 A6 1 0;48 B6 1 0;50 A6 1 0;52 G#6 1 0;54 A6 1 0;56 C7 1 0;56 A3 1 0;60 C4 1 0;64 C4 1 0;68 C4 1 0;60 E4 1 0;64 E4 1 0;68 E4 1 0;72 E3 1 0;76 E4 1 0;80 E4 1 0;84 E4 1 0;88 E3 1 0;92 E4 1 0;96 E4 1 0;100 E4 1 0;104 E3 1 0;108 E4 1 0;112 B2 1 0;116 B3 1 0;120 E3 1 0;92 B3 1 0;96 B3 1 0;100 B3 1 0;108 B3 1 0;84 B3 1 0;80 B3 1 0;76 B3 1 0;64 A6 1 0;68 C7 1 0;72 G6 1 0;72 B6 1 0;76 F#6 1 0;76 A6 1 0;80 E6 1 0;80 G6 1 0;84 A6 1 0;84 F#6 1 0;88 G6 1 0;88 B6 1 0;92 F#6 1 0;92 A6 1 0;96 E6 1 0;96 G6 1 0;100 F#6 1 0;100 A6 1 0;104 B6 1 0;104 G6 1 0;108 A6 1 0;108 F#6 1 0;116 F#6 1 0;116 D#6 1 0;120 E6 1 0;112 E6 1 0;112 G6 1 0;128 B5 1 0;130 A5 1 0;132 G#5 1 0;134 A5 1 0;136 C6 1 0;144 D6 1 0;146 C6 1 0;148 B5 1 0;150 C6 1 0;152 E6 1 0;160 F6 1 0;162 E6 1 0;164 D#6 1 0;166 E6 1 0;168 B6 1 0;170 A6 1 0;172 G#6 1 0;174 A6 1 0;176 B6 1 0;178 A6 1 0;180 G#6 1 0;182 A6 1 0;184 C7 1 0;192 A6 1 0;196 C7 1 0;200 B6 1 0;200 G6 1 0;204 A6 1 0;208 G6 1 0;212 A6 1 0;216 B6 1 0;220 A6 1 0;224 G6 1 0;228 A6 1 0;232 B6 1 0;236 A6 1 0;240 G6 1 0;204 F#6 1 0;208 E6 1 0;212 F#6 1 0;216 G6 1 0;220 F#6 1 0;224 E6 1 0;228 F#6 1 0;232 G6 1 0;236 F#6 1 0;240 E6 1 0;244 F#6 1 0;244 D#6 1 0;248 E6 1 0;136 A3 1 0;140 C4 1 0;140 E4 1 0;144 E4 1 0;144 C4 1 0;148 C4 1 0;148 E4 1 0;152 A3 1 0;156 C4 1 0;160 C4 1 0;164 C4 1 0;156 E4 1 0;160 E4 1 0;164 E4 1 0;168 A3 1 0;172 C4 1 0;172 E4 1 0;176 A3 1 0;180 C4 1 0;180 E4 1 0;184 A3 1 0;188 C4 1 0;188 E4 1 0;192 E4 1 0;196 E4 1 0;192 C4 1 0;196 C4 1 0;204 E4 1 0;208 E4 1 0;212 E4 1 0;204 B3 1 0;208 B3 1 0;212 B3 1 0;220 B3 1 0;224 B3 1 0;228 B3 1 0;220 E4 1 0;224 E4 1 0;228 E4 1 0;236 B3 1 0;236 E4 1 0;216 E3 1 0;232 E3 1 0;200 E3 1 0;240 B2 1 0;244 B3 1 0;248 E3 1 0;256 C6 1 0;256 E6 1 0;260 F6 1 0;264 G6 1 0;268 G6 1 0;260 D6 1 0;264 E6 1 0;268 E6 1 0;272 A6 1 0;274 G6 1 0;276 F6 1 0;278 E6 1 0;280 D6 1 0;288 C6 1 0;288 E6 1 0;292 D6 1 0;292 F6 1 0;296 E6 1 0;296 G6 1 0;300 E6 1 0;300 G6 1 0;304 A6 1 0;306 G6 1 0;308 F6 1 0;310 E6 1 0;312 D6 1 0;320 C6 1 0;324 D6 1 0;328 E6 1 0;332 E6 1 0;320 A5 1 0;324 B5 1 0;328 C6 1 0;332 C6 1 0;280 B5 1 0;284 G5 1 0;336 F6 1 0;338 E6 1 0;340 D6 1 0;342 C6 1 0;344 B5 1 0;344 G#5 1 0;348 E5 1 0;352 A5 1 0;352 C6 1 0;356 B5 1 0;356 D6 1 0;360 C6 1 0;360 E6 1 0;364 E6 1 0;364 C6 1 0;368 F6 1 0;370 E6 1 0;372 D6 1 0;374 C6 1 0;376 B5 1 0;384 B5 1 0;386 A5 1 0;388 G#5 1 0;390 A5 1 0;392 C6 1 0;400 D6 1 0;402 C6 1 0;404 B5 1 0;406 C6 1 0;408 E6 1 0;416 F6 1 0;418 E6 1 0;420 D#6 1 0;422 E6 1 0;424 B6 1 0;428 G#6 1 0;426 A6 1 0;430 A6 1 0;432 B6 1 0;434 A6 1 0;436 G#6 1 0;438 A6 1 0;440 C7 1 0;448 A6 1 0;464 A6 1 0;468 G#6 1 0;472 A6 1 0;452 B6 1 0;456 C7 1 0;460 B6 1 0;476 E6 1 0;480 F6 1 0;484 D6 1 0;488 C6 1 0;496 B5 1 0;497 C6 1 0;498 B5 1 0;499 C6 1 0;500 B5 1 0;501 C6 1 0;502 B5 1 0;504 A5 1 0;512 A5 1 0;516 B5 1 0;520 C#6 1 0;528 A5 1 0;532 B5 1 0;536 C#6 1 0;540 B5 1 0;544 A5 1 0;548 G#5 1 0;552 F#5 1 0;556 G#5 1 0;560 A5 1 0;564 B5 1 0;568 G#5 1 0;572 E5 1 0;528 A6 1 0;532 B6 1 0;536 C#7 1 0;512 A6 1 0;516 B6 1 0;520 C#7 1 0;540 B6 1 0;544 A6 1 0;548 G#6 1 0;552 F#6 1 0;556 G#6 1 0;568 G#6 1 0;560 A6 1 0;564 B6 1 0;572 E6 1 0;264 C3 1 0;268 C4 1 0;272 E3 1 0;276 E4 1 0;280 G3 1 0;296 C3 1 0;300 C4 1 0;304 E3 1 0;308 E4 1 0;312 G3 1 0;328 A2 1 0;332 A3 1 0;336 C3 1 0;340 C4 1 0;344 E3 1 0;360 A2 1 0;364 A3 1 0;368 C3 1 0;372 C4 1 0;376 E3 1 0;392 A3 1 0;396 C4 1 0;396 E4 1 0;400 E4 1 0;400 C4 1 0;404 C4 1 0;404 E4 1 0;408 A3 1 0;412 C4 1 0;412 E4 1 0;416 E4 1 0;420 E4 1 0;420 C4 1 0;416 C4 1 0;424 A3 1 0;428 C4 1 0;428 E4 1 0;432 A3 1 0;436 C4 1 0;436 E4 1 0;440 F3 1 0;444 A3 1 0;444 D#4 1 0;448 A3 1 0;448 D#4 1 0;452 D#4 1 0;452 A3 1 0;456 E3 1 0;460 A3 1 0;460 E4 1 0;464 D3 1 0;468 F3 1 0;468 B3 1 0;472 C3 1 0;476 E3 1 0;476 A3 1 0;480 D3 1 0;484 F3 1 0;484 B3 1 0;488 A3 1 0;488 E3 1 0;492 E3 1 0;492 A3 1 0;496 E3 1 0;496 G#3 1 0;500 E3 1 0;500 G#3 1 0;504 A3 1 0;504 A2 1 0;520 A2 1 0;524 A3 1 0;528 A3 1 0;532 A3 1 0;536 A2 1 0;540 A3 1 0;544 A3 1 0;548 A3 1 0;556 D3 1 0;552 D2 1 0;560 D#2 1 0;564 D#3 1 0;568 E2 1 0;572 E3 1 0;576 E3 1 0;580 E3 1 0;576 A5 1 0;580 B5 1 0;584 C#6 1 0;592 A5 1 0;596 B5 1 0;600 C#6 1 0;604 B5 1 0;608 A5 1 0;612 G#5 1 0;616 F#5 1 0;620 B5 1 0;624 G#5 1 0;628 E5 1 0;632 A5 1 0;580 B6 1 0;584 C#7 1 0;596 B6 1 0;600 C#7 1 0;576 A6 1 0;592 A6 1 0;604 B6 1 0;608 A6 1 0;612 G#6 1 0;616 F#6 1 0;620 B6 1 0;624 G#6 1 0;628 E6 1 0;632 A6 1 0;640 A5 1 0;640 A6 1 0;644 B5 1 0;648 C#6 1 0;656 A5 1 0;660 B5 1 0;664 C#6 1 0;644 B6 1 0;648 C#7 1 0;656 A6 1 0;660 B6 1 0;664 C#7 1 0;668 B5 1 0;672 A5 1 0;676 G#5 1 0;680 F#5 1 0;684 G#5 1 0;688 A5 1 0;692 B5 1 0;696 G#5 1 0;700 E5 1 0;668 B6 1 0;672 A6 1 0;676 G#6 1 0;680 F#6 1 0;684 G#6 1 0;688 A6 1 0;692 B6 1 0;696 G#6 1 0;700 E6 1 0;704 A5 1 0;708 B5 1 0;712 C#6 1 0;720 A5 1 0;724 B5 1 0;728 C#6 1 0;732 B5 1 0;736 A5 1 0;740 G#5 1 0;744 F#5 1 0;748 B5 1 0;752 G#5 1 0;756 E5 1 0;760 A5 1 0;704 A6 1 0;708 B6 1 0;712 C#7 1 0;720 A6 1 0;724 B6 1 0;728 C#7 1 0;732 B6 1 0;736 A6 1 0;740 G#6 1 0;744 F#6 1 0;748 B6 1 0;752 G#6 1 0;756 E6 1 0;760 A6 1 0;584 A2 1 0;588 A3 1 0;592 A3 1 0;596 A3 1 0;600 A2 1 0;604 A3 1 0;608 A3 1 0;612 A3 1 0;616 D2 1 0;620 D3 1 0;624 E2 1 0;628 E3 1 0;632 A2 1 0;636 A3 1 0;640 A3 1 0;644 A3 1 0;648 A2 1 0;652 A3 1 0;656 A3 1 0;660 A3 1 0;664 A2 1 0;668 A3 1 0;672 A3 1 0;676 A3 1 0;680 D2 1 0;684 D3 1 0;688 D#2 1 0;700 E3 1 0;692 D#3 1 0;696 E2 1 0;704 E3 1 0;708 E3 1 0;712 A2 1 0;716 A3 1 0;720 A3 1 0;724 A3 1 0;728 A2 1 0;732 A3 1 0;736 A3 1 0;740 A3 1 0;744 D2 1 0;748 D3 1 0;752 E2 1 0;756 E3 1 0;760 A2 1 0;768 C#7 1 0;768 C#6 1 0;773 C#7 1 0;773 C#6 1 0;775 E6 1 0;775 A6 1 0;775 C#7 1 0;792 C#7 1 0;792 A6 1 0;792 E6 1 0;808 D7 1 0;810 C#7 1 0;812 B6 1 0;814 C#7 1 0;816 D7 1 0;818 C#7 1 0;820 B6 1 0;822 C#7 1 0;824 D7 1 0;824 A6 1 0;824 F#6 1 0;840 C#7 1 0;840 E6 1 0;840 A6 1 0;844 C#7 1 0;848 C#7 1 0;844 A6 1 0;844 E6 1 0;848 E6 1 0;848 A6 1 0;852 E6 1 0;906 C#7 1 0;910 C#7 1 0;914 C#7 1 0;952 B6 1 0;956 B6 1 0;952 G#6 1 0;956 G#6 1 0;956 E6 1 0;952 E6 1 0;856 E6 1 0;856 G#6 1 0;856 B6 1 0;852 A6 1 0;852 C#7 1 0;868 E7 1 0;872 C#7 1 0;872 A6 1 0;872 E6 1 0;888 E6 1 0;888 A6 1 0;888 C#7 1 0;904 D7 1 0;908 B6 1 0;912 D7 1 0;916 B6 1 0;918 C#7 1 0;920 D7 1 0;920 A6 1 0;920 F#6 1 0;932 D7 1 0;936 C#7 1 0;936 A6 1 0;936 E6 1 0;960 B6 1 0;964 B6 1 0;960 G#6 1 0;960 E6 1 0;964 E6 1 0;964 G#6 1 0;968 C#6 1 0;968 E6 1 0;968 A6 1 0;980 C#6 1 0;980 C#7 1 0;984 A5 1 0;984 A6 1 0;996 E7 1 0;996 E6 1 0;1000 A5 1 0;1000 A6 1 0;1012 C#6 1 0;1016 A5 1 0;1012 C#7 1 0;1016 A6 1 0;1020 C#7 1 0;1024 A6 1 0;1020 C#6 1 0;1024 A5 1 0;1028 E7 1 0;1028 E6 1 0;1032 A6 1 0;1032 A5 1 0;1040 A6 1 0;1040 E6 1 0;1040 C#6 1 0;1048 A6 1 0;1048 E6 1 0;1048 C#6 1 0;764 A3 1 0;768 A3 1 0;772 A3 1 0;776 A2 1 0;780 A3 1 0;784 A3 1 0;788 A3 1 0;792 A2 1 0;796 A3 1 0;800 A3 1 0;804 A3 1 0;808 A2 1 0;812 A3 1 0;816 A3 1 0;820 A3 1 0;824 D2 1 0;828 D3 1 0;832 D3 1 0;836 D3 1 0;840 A2 1 0;844 A3 1 0;848 A3 1 0;852 A3 1 0;856 E2 1 0;860 E3 1 0;864 E3 1 0;868 E3 1 0;872 A2 1 0;876 A3 1 0;880 A3 1 0;884 A3 1 0;888 A2 1 0;892 A3 1 0;896 A3 1 0;900 A3 1 0;904 A2 1 0;908 A3 1 0;912 A3 1 0;916 A3 1 0;920 D2 1 0;924 D3 1 0;928 D3 1 0;932 D3 1 0;936 A2 1 0;940 A3 1 0;944 A3 1 0;948 A3 1 0;952 E2 1 0;956 E3 1 0;960 E3 1 0;964 E3 1 0;968 A2 1 0;972 A3 1 0;976 A3 1 0;980 A3 1 0;984 A2 1 0;988 A3 1 0;992 A3 1 0;996 A3 1 0;1000 A2 1 0;1004 A3 1 0;1008 A3 1 0;1012 A3 1 0;1016 A2 1 0;1016 A3 1 0;1020 A3 1 0;1024 A2 1 0;1024 A3 1 0;1028 A2 1 0;1032 A2 1 0;1032 A3 1 0;1040 A2 1 0;1048 A2 1 0"
class music:
    def __init__(self, songString='0 D4 8 0', mux=False):
        self.tempo = 1
        self.song = songString
        self.looping = False
        self.mux = mux
 
        self.stopped = False
 
        self.timer = -1
        self.beat = -1
        self.arpnote = 0
 
        self.notes = []
 
        self.playingNotes = []
        self.playingDurations = []
 
 
        #Find the end of the song
        self.end = 0
        splitSong = self.song.split(";")
        for note in splitSong:
            snote = note.split(" ")
            testEnd = round(float(snote[0])) + ceil(float(snote[2]))
            if (testEnd > self.end):
                self.end = testEnd
 
        #Create empty song structure
        while (self.end > len(self.notes)):
            self.notes.append(None)
 
        #Populate song structure with the notes
        for note in splitSong:
            snote = note.split(" ")
            beat = round(float(snote[0]))
 
            if (self.notes[beat] == None):
                self.notes[beat] = []
            self.notes[beat].append([snote[1],ceil(float(snote[2]))]) #Note, Duration
 
 
        #Round up end of song to nearest bar
        self.end = ceil(self.end / 8) * 8
 
    def stop(self):
        self.stopped = True
 
    def tick(self):
        if (not self.stopped):
            self.timer = self.timer + 1
 
            #Loop
            if (self.timer % (self.tempo * self.end) == 0 and (not (self.timer == 0))):
                if (not self.looping):
                    self.stop()
                    return False
                self.beat = -1
                self.timer = 0
 
            #On Beat
            if (self.timer % self.tempo == 0):
                self.beat = self.beat + 1
 
                #Remove expired notes from playing list
                i = 0
                while (i < len(self.playingDurations)):
                    self.playingDurations[i] = self.playingDurations[i] - 1
                    if (self.playingDurations[i] <= 0):
                        self.playingNotes.pop(i)
                        self.playingDurations.pop(i)
                    else:
                        i = i + 1
 
                #Add new notes and their durations to the playing list
 
                """
                #Old method runs for every note, slow to process on every beat and causes noticeable delay
                ssong = song.split(";")
                for note in ssong:
                    snote = note.split(" ")
                    if int(snote[0]) == beat:
                        playingNotes.append(snote[1])
                        playingDurations.append(int(snote[2]))
                """
 
                if (self.beat < len(self.notes)):
                    if (self.notes[self.beat] != None):
                        for note in self.notes[self.beat]:
                            self.playingNotes.append(note[0])
                            self.playingDurations.append(note[1])
 
                #Only need to run these checks on beats
                i = 0
                if (i >= len(self.playingNotes)):
                    print('#', end=',')
                else:
                    #Play note
                    print(self.playingNotes[i], end=',')
                    i = i + 1
 
 
            #Play arp of all playing notes
            if (len(self.playingNotes) > 1):
                if (self.arpnote > len(self.playingNotes)-1):
                    self.arpnote = 0
                #多通道
                if self.mux:
                    print(self.playingNotes[self.arpnote], end=',')
                self.arpnote = self.arpnote + 1
 
            return True
        else:
            return False


if __name__ == '__main__':
    mySong = music(song2, True)
    while mySong.tick():
        pass
