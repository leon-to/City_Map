#include <random>
#include <unittest++/UnitTest++.h>

#include "StreetsDatabaseAPI.h"
#include "m1.h"
#include "m3.h"

#include "unit_test_util.h"
#include "path_verify.h"

using ece297test::relative_error;
using ece297test::path_is_legal;

struct MapFixture {
    MapFixture() {
        rng = std::minstd_rand(0);
        rand_intersection = std::uniform_int_distribution<unsigned>(0, getNumberOfIntersections()-1);
        rand_street = std::uniform_int_distribution<unsigned>(1, getNumberOfStreets()-1);
        rand_segment = std::uniform_int_distribution<unsigned>(0, getNumberOfStreetSegments()-1);
        rand_poi = std::uniform_int_distribution<unsigned>(0, getNumberOfPointsOfInterest()-1);
        rand_lat = std::uniform_real_distribution<float>(43.48, 43.91998);
        rand_lon = std::uniform_real_distribution<float>(-79.78998, -79.00001);
    }

    std::minstd_rand rng;
    std::uniform_int_distribution<unsigned> rand_intersection;
    std::uniform_int_distribution<unsigned> rand_street;
    std::uniform_int_distribution<unsigned> rand_segment;
    std::uniform_int_distribution<unsigned> rand_poi;
    std::uniform_real_distribution<float> rand_lat;
    std::uniform_real_distribution<float> rand_lon;
};

SUITE(inter_poi_path_func_public) {
    TEST(find_path_to_point_of_interest_functionality) {
        std::vector<unsigned> path;
        std::vector<unsigned> valid_end_intersections;
        double path_cost;
        
        valid_end_intersections = {105444, 12425, 14609, 18768, 5184, 2290, 41909, 1745, 58152, 87075, 4712, 15309, 16690, 12788, 33025, 7766, 2277, 36641, 21369, 1666, 2125, 23135, 3394, 15228, 20195, 1113, 1080, 71671, 101438, 33279, 72235, 102554, 54322, 95335, 31988, 26814, 96942, 101800, 74932, 43196, 8192, 36298, 23842, 8874, 96170, 41904, 28591, 28896, 9799, 1272, 2600, 21238, 59297, 6779, 45677, 92099, 68036, 81392, 105975, 106581, 1870, 95400, 96689, 54015, 44157, 60874, 72563, 61229, 20009, 84777, 79040, 102490, 90879, 6152, 47606, 53501, 1949, 60378, 2243, 6867, 5510, 11261, 16263, 90758, 70075, 44349, 20232, 1792, 5176, 71114, 98946, 1422, 51282, 35154, 13097, 14985, 97865, 5198, 1131, 3984, 41268, 76172, 75682, 2272, 4017, 75739, 31198, 32076, 95943, 1744, 77284, 23975, 28331, 82477, 105838, 106166, 2270, 50317, 33060, 74417, 90256, 104623, 30926, 82001, 58307, 61331, 99545, 5814, 96062, 10562, 96525, 6056, 45674, 79798, 4016, 70806, 11348, 67447, 78734, 78718, 69926, 82046, 25311, 26564, 10496, 90120, 40907, 42219, 96908, 55962, 25923, 71477, 33281, 44748, 24805, 70646, 108023, 33024, 58772, 81880, 84593, 60721, 58790, 18982, 94170, 63869, 95305, 23034, 22959, 96293, 35061, 35582, 22612, 39503, 26474, 7801, 9714, 89550, 34721, 67695, 86620, 97329, 16770, 79726, 50621, 50542, 41887, 83219, 106040, 99329, 15793, 5458, 98781, 22107, 99294, 100639, 101455, 36512, 42192, 69946, 19145, 1897, 7743, 92199, 25414, 1047, 4631, 79345, 45499, 82021, 6514, 23412, 100133, 1744, 1059, 53719, 100647, 4303, 74077, 79885, 1353, 107455, 56415, 5093, 22698, 35110, 97748, 79631, 727, 6668, 45124, 59967, 82274, 107639, 99904, 73443, 107650, 27011, 13495, 52477, 82678, 13027, 93607, 29584};
        path = find_path_to_point_of_interest(9672, "Tim Hortons");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(9672, valid_end_intersections, path));
        CHECK(path_cost <= 11.40146041953046);
        
        valid_end_intersections = {5204, 45670, 5185, 82551, 1487, 1833, 12572, 11031, 513, 6997, 63067, 97836, 4182, 727, 16674, 81174, 2259, 45089, 3340, 2292, 9236, 70897, 95463, 18670, 99114, 93480, 1078, 23113, 59300, 20194, 10869, 11016, 24460, 10077, 99992, 2955, 7359, 57768, 23035, 57420, 2142, 4320, 14601, 45640, 107820, 57809, 4756, 62134, 61721, 25555, 21033, 21437, 1219, 69668, 54322, 35151, 56405, 15076, 19848, 41888, 82161, 45499, 88579, 44755, 36643, 57025, 11621, 35124, 2277, 13491, 103732, 78869, 98642, 50657, 4297, 13280, 103325, 20697, 7374, 90859, 70714, 85313, 70080, 30545, 13547, 91, 89185, 16270, 101013, 86929, 11652, 71366, 55837, 51470, 62041, 98166, 67837, 1014, 72647, 72722, 13509, 78657, 90530, 20573, 31198, 75072, 2616, 61318, 78708, 79851, 12380, 31088, 39914, 100978, 59011, 41993, 83226, 20638, 58307, 44748, 108439, 94713, 71708, 41888, 49570, 28929, 10705, 14875, 15327, 96378, 102316, 26561, 31353, 31436, 90149, 86671, 92235, 90611, 105177, 33433, 34329, 16982, 105008, 105754, 10654, 73025, 76161, 89164, 41888, 91364, 22203, 64251, 97329, 96696, 21220, 97512, 5454, 13479, 106280, 35327, 3339, 19847, 24385, 45095, 34069, 86359, 91838, 53707, 36467, 79328, 2569, 91665, 7830, 52498, 6652, 32341, 106756, 63321, 49388, 101345, 93394, 103775, 103980, 18532, 49629, 93660};
        path = find_path_to_point_of_interest(16427, "TD Canada Trust");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(16427, valid_end_intersections, path));
        CHECK(path_cost <= 2.918858378412318);
        
        valid_end_intersections = {82463, 7260, 5590, 12433, 12052, 4320, 61321, 94640, 72385, 93575, 84, 50648, 38399, 19295, 68318, 73691, 1734, 63154, 59027, 19205, 82796, 52818, 59855, 14026, 57661, 57240, 61389, 21993, 34993, 4757, 35151, 77462, 27358, 61365, 62142, 26845, 93032, 42895, 7743, 40908, 41828, 52515, 88287, 54672, 88337, 19150, 1338, 57691, 60371, 30348, 37284, 8082, 98165, 54838, 62321, 90671, 29824, 98646, 10463, 51494, 57906, 49973, 77878, 73305, 62003, 88171, 31376, 75744, 71030, 46469, 67773, 86509, 59739, 1215, 1259, 26339, 106362, 34537, 97208, 44990, 56415, 26382, 14486, 107633, 66380, 60901, 70933, 52441, 60608, 18520, 72667, 63418, 106837, 33322, 82691};
        path = find_path_to_point_of_interest(2, "Shell");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(2, valid_end_intersections, path));
        CHECK(path_cost <= 3.576138618193494);
        
        valid_end_intersections = {44616};
        path = find_path_to_point_of_interest(22444, "Nirvana");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(22444, valid_end_intersections, path));
        CHECK(path_cost <= 16.31553549357065);
        
        valid_end_intersections = {105444, 12425, 14609, 18768, 5184, 2290, 41909, 1745, 58152, 87075, 4712, 15309, 16690, 12788, 33025, 7766, 2277, 36641, 21369, 1666, 2125, 23135, 3394, 15228, 20195, 1113, 1080, 71671, 101438, 33279, 72235, 102554, 54322, 95335, 31988, 26814, 96942, 101800, 74932, 43196, 8192, 36298, 23842, 8874, 96170, 41904, 28591, 28896, 9799, 1272, 2600, 21238, 59297, 6779, 45677, 92099, 68036, 81392, 105975, 106581, 1870, 95400, 96689, 54015, 44157, 60874, 72563, 61229, 20009, 84777, 79040, 102490, 90879, 6152, 47606, 53501, 1949, 60378, 2243, 6867, 5510, 11261, 16263, 90758, 70075, 44349, 20232, 1792, 5176, 71114, 98946, 1422, 51282, 35154, 13097, 14985, 97865, 5198, 1131, 3984, 41268, 76172, 75682, 2272, 4017, 75739, 31198, 32076, 95943, 1744, 77284, 23975, 28331, 82477, 105838, 106166, 2270, 50317, 33060, 74417, 90256, 104623, 30926, 82001, 58307, 61331, 99545, 5814, 96062, 10562, 96525, 6056, 45674, 79798, 4016, 70806, 11348, 67447, 78734, 78718, 69926, 82046, 25311, 26564, 10496, 90120, 40907, 42219, 96908, 55962, 25923, 71477, 33281, 44748, 24805, 70646, 108023, 33024, 58772, 81880, 84593, 60721, 58790, 18982, 94170, 63869, 95305, 23034, 22959, 96293, 35061, 35582, 22612, 39503, 26474, 7801, 9714, 89550, 34721, 67695, 86620, 97329, 16770, 79726, 50621, 50542, 41887, 83219, 106040, 99329, 15793, 5458, 98781, 22107, 99294, 100639, 101455, 36512, 42192, 69946, 19145, 1897, 7743, 92199, 25414, 1047, 4631, 79345, 45499, 82021, 6514, 23412, 100133, 1744, 1059, 53719, 100647, 4303, 74077, 79885, 1353, 107455, 56415, 5093, 22698, 35110, 97748, 79631, 727, 6668, 45124, 59967, 82274, 107639, 99904, 73443, 107650, 27011, 13495, 52477, 82678, 13027, 93607, 29584};
        path = find_path_to_point_of_interest(10168, "Tim Hortons");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(10168, valid_end_intersections, path));
        CHECK(path_cost <= 3.992551157558185);
        
        valid_end_intersections = {12913, 3933, 18627, 18798, 23133, 19081, 54335, 48990, 53540, 35824, 49794, 59487, 69668, 72384, 8994, 3705, 28896, 4320, 19156, 4197, 81984, 100275, 106566, 56389, 52373, 53502, 10070, 15646, 71793, 71027, 71564, 62070, 54633, 5198, 77731, 52965, 77399, 2506, 5184, 46775, 79525, 33651, 26561, 94157, 58670, 105755, 90150, 96138, 23333, 16513, 34424, 27882, 92790, 96346, 8596, 3172};
        path = find_path_to_point_of_interest(4501, "Mr. Sub");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(4501, valid_end_intersections, path));
        CHECK(path_cost <= 3.524752465574961);
        
        valid_end_intersections = {5204, 45670, 5185, 82551, 1487, 1833, 12572, 11031, 513, 6997, 63067, 97836, 4182, 727, 16674, 81174, 2259, 45089, 3340, 2292, 9236, 70897, 95463, 18670, 99114, 93480, 1078, 23113, 59300, 20194, 10869, 11016, 24460, 10077, 99992, 2955, 7359, 57768, 23035, 57420, 2142, 4320, 14601, 45640, 107820, 57809, 4756, 62134, 61721, 25555, 21033, 21437, 1219, 69668, 54322, 35151, 56405, 15076, 19848, 41888, 82161, 45499, 88579, 44755, 36643, 57025, 11621, 35124, 2277, 13491, 103732, 78869, 98642, 50657, 4297, 13280, 103325, 20697, 7374, 90859, 70714, 85313, 70080, 30545, 13547, 91, 89185, 16270, 101013, 86929, 11652, 71366, 55837, 51470, 62041, 98166, 67837, 1014, 72647, 72722, 13509, 78657, 90530, 20573, 31198, 75072, 2616, 61318, 78708, 79851, 12380, 31088, 39914, 100978, 59011, 41993, 83226, 20638, 58307, 44748, 108439, 94713, 71708, 41888, 49570, 28929, 10705, 14875, 15327, 96378, 102316, 26561, 31353, 31436, 90149, 86671, 92235, 90611, 105177, 33433, 34329, 16982, 105008, 105754, 10654, 73025, 76161, 89164, 41888, 91364, 22203, 64251, 97329, 96696, 21220, 97512, 5454, 13479, 106280, 35327, 3339, 19847, 24385, 45095, 34069, 86359, 91838, 53707, 36467, 79328, 2569, 91665, 7830, 52498, 6652, 32341, 106756, 63321, 49388, 101345, 93394, 103775, 103980, 18532, 49629, 93660};
        path = find_path_to_point_of_interest(43148, "TD Canada Trust");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(43148, valid_end_intersections, path));
        CHECK(path_cost <= 4.318390847120953);
        
        valid_end_intersections = {105444, 12425, 14609, 18768, 5184, 2290, 41909, 1745, 58152, 87075, 4712, 15309, 16690, 12788, 33025, 7766, 2277, 36641, 21369, 1666, 2125, 23135, 3394, 15228, 20195, 1113, 1080, 71671, 101438, 33279, 72235, 102554, 54322, 95335, 31988, 26814, 96942, 101800, 74932, 43196, 8192, 36298, 23842, 8874, 96170, 41904, 28591, 28896, 9799, 1272, 2600, 21238, 59297, 6779, 45677, 92099, 68036, 81392, 105975, 106581, 1870, 95400, 96689, 54015, 44157, 60874, 72563, 61229, 20009, 84777, 79040, 102490, 90879, 6152, 47606, 53501, 1949, 60378, 2243, 6867, 5510, 11261, 16263, 90758, 70075, 44349, 20232, 1792, 5176, 71114, 98946, 1422, 51282, 35154, 13097, 14985, 97865, 5198, 1131, 3984, 41268, 76172, 75682, 2272, 4017, 75739, 31198, 32076, 95943, 1744, 77284, 23975, 28331, 82477, 105838, 106166, 2270, 50317, 33060, 74417, 90256, 104623, 30926, 82001, 58307, 61331, 99545, 5814, 96062, 10562, 96525, 6056, 45674, 79798, 4016, 70806, 11348, 67447, 78734, 78718, 69926, 82046, 25311, 26564, 10496, 90120, 40907, 42219, 96908, 55962, 25923, 71477, 33281, 44748, 24805, 70646, 108023, 33024, 58772, 81880, 84593, 60721, 58790, 18982, 94170, 63869, 95305, 23034, 22959, 96293, 35061, 35582, 22612, 39503, 26474, 7801, 9714, 89550, 34721, 67695, 86620, 97329, 16770, 79726, 50621, 50542, 41887, 83219, 106040, 99329, 15793, 5458, 98781, 22107, 99294, 100639, 101455, 36512, 42192, 69946, 19145, 1897, 7743, 92199, 25414, 1047, 4631, 79345, 45499, 82021, 6514, 23412, 100133, 1744, 1059, 53719, 100647, 4303, 74077, 79885, 1353, 107455, 56415, 5093, 22698, 35110, 97748, 79631, 727, 6668, 45124, 59967, 82274, 107639, 99904, 73443, 107650, 27011, 13495, 52477, 82678, 13027, 93607, 29584};
        path = find_path_to_point_of_interest(42823, "Tim Hortons");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(42823, valid_end_intersections, path));
        CHECK(path_cost <= 2.704866167446373);
        
        valid_end_intersections = {80263, 2125, 41447, 1316, 9964, 11321, 2387, 11876, 3229, 103058, 70936, 11985, 3944, 16762, 45680, 14601, 74426, 4310, 18627, 97181, 103430, 10854, 5176, 4183, 99992, 7849, 52792, 57675, 2142, 33052, 33061, 3510, 81988, 54325, 31979, 61275, 26800, 61721, 108067, 35994, 91835, 36637, 16674, 72383, 14121, 89171, 44639, 58442, 5403, 24656, 16771, 18157, 98617, 51225, 55854, 88675, 93931, 70066, 5812, 92171, 6339, 14229, 55444, 5703, 36300, 98946, 71394, 6104, 71967, 28591, 68889, 2309, 41178, 75677, 72066, 105467, 73513, 8172, 38952, 82897, 58757, 54746, 70336, 92396, 1080, 58307, 6514, 10006, 31104, 67229, 28492, 26563, 74230, 1702, 24818, 24732, 105755, 95439, 76109, 89164, 11621, 10351, 26378, 8502, 22430, 35286, 19837, 80609, 58778, 104991, 11809, 19422, 56273, 73523, 91457, 94618, 101407, 63320, 101339, 82702, 5597, 5570};
        path = find_path_to_point_of_interest(47772, "Pizza Pizza");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(47772, valid_end_intersections, path));
        CHECK(path_cost <= 7.844468973248699);
        
        valid_end_intersections = {82104};
        path = find_path_to_point_of_interest(52747, "Blumont Bistro");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(52747, valid_end_intersections, path));
        CHECK(path_cost <= 18.93797118659853);
        
        valid_end_intersections = {241, 59292, 18797, 102703, 105955, 18480, 88403, 12790, 71555, 24961, 66412, 16774, 8586, 52498, 15040, 95457, 88451, 18402, 76168, 85695, 79879, 9937, 67837, 41902, 27093, 82738, 39706, 36957, 33435, 31340, 1651, 60527, 90216, 83793, 1587, 48861, 25585, 94618, 78585};
        path = find_path_to_point_of_interest(54883, "Swiss Chalet");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(54883, valid_end_intersections, path));
        CHECK(path_cost <= 6.774841700851454);
        
        valid_end_intersections = {102025, 6339, 1606, 12751, 2376, 2324, 2290, 20025, 69682, 14820, 29104, 86232, 7765, 16975, 1014, 9244, 21369, 103429, 24460, 16462, 85315, 29210, 2954, 98707, 101446, 99962, 31614, 57675, 17010, 92414, 12581, 71793, 49815, 77452, 91245, 92502, 61261, 49579, 22702, 33213, 35826, 61521, 42735, 36000, 59406, 103939, 35151, 54004, 19844, 29581, 16757, 33014, 70058, 41887, 1451, 44754, 24760, 31089, 31857, 106573, 101979, 107521, 68572, 4309, 103323, 103248, 98622, 62004, 23686, 7225, 60370, 90042, 92175, 61318, 6724, 20730, 98946, 11442, 107221, 62041, 12338, 79040, 71545, 70909, 68931, 72646, 41218, 75682, 76109, 90534, 56109, 73344, 75072, 81689, 50236, 100978, 101900, 70747, 8233, 2272, 74435, 24813, 82898, 83204, 96009, 67794, 1387, 6056, 2242, 23123, 10854, 87690, 90, 66053, 66552, 36589, 81814, 90600, 57025, 33577, 32573, 24733, 3803, 98153, 99122, 105007, 725, 84727, 75746, 34810, 90766, 22148, 22525, 36643, 55855, 21221, 99329, 71569, 63993, 21715, 61723, 4650, 25731, 45402, 56308, 87078, 78708, 41490, 68958, 102029, 61137, 6668, 104741, 59974, 63316, 93394, 27002, 80410, 13495, 59482, 103983, 35794, 105725};
        path = find_path_to_point_of_interest(58853, "Shoppers Drug Mart");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(58853, valid_end_intersections, path));
        CHECK(path_cost <= 3.488990021124339);
        
        valid_end_intersections = {2685, 99066, 33018, 2125, 16770, 16580, 1051, 1015, 4111, 14599, 89257, 44066, 99102, 103428, 8158, 12620, 1082, 26238, 23841, 1656, 4188, 4016, 49619, 82104, 3705, 93483, 36643, 36644, 79574, 28493, 60849, 71749, 38951, 14229, 16657, 2394, 26674, 6859, 8876, 52381, 2241, 70448, 9388, 14595, 87691, 79156, 28633, 29789, 12103, 2273, 4017, 1884, 96007, 9937, 14122, 19348, 62042, 50677, 16765, 2248, 2363, 91936, 10040, 87695, 98161, 41909, 34191, 92165, 32507, 90613, 104991, 48990, 104555, 97511, 60705, 4016, 74560, 82652, 7711, 32553, 94484, 73509, 1057, 3950, 63294, 93128, 73512, 105736, 1813, 4182, 94618, 62043, 91452, 82569, 43067};
        path = find_path_to_point_of_interest(59870, "Second Cup");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(59870, valid_end_intersections, path));
        CHECK(path_cost <= 7.288782476808191);
        
        valid_end_intersections = {20125};
        path = find_path_to_point_of_interest(61340, "Clarkson Montessori School");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(61340, valid_end_intersections, path));
        CHECK(path_cost <= 33.27888336124622);
        
        valid_end_intersections = {11504};
        path = find_path_to_point_of_interest(70550, "Florentia Ristorante");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(70550, valid_end_intersections, path));
        CHECK(path_cost <= 19.43104924063637);
        
        valid_end_intersections = {35795, 47886, 28897, 52028, 75682, 93877, 74813, 89921, 79523, 67623, 60732, 97220, 99235, 83892};
        path = find_path_to_point_of_interest(26565, "Kelsey's");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(26565, valid_end_intersections, path));
        CHECK(path_cost <= 4.349855073036835);
        
        valid_end_intersections = {80949};
        path = find_path_to_point_of_interest(75396, "Maple Education");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(75396, valid_end_intersections, path));
        CHECK(path_cost <= 29.00910961786277);
        
        valid_end_intersections = {102025, 6339, 1606, 12751, 2376, 2324, 2290, 20025, 69682, 14820, 29104, 86232, 7765, 16975, 1014, 9244, 21369, 103429, 24460, 16462, 85315, 29210, 2954, 98707, 101446, 99962, 31614, 57675, 17010, 92414, 12581, 71793, 49815, 77452, 91245, 92502, 61261, 49579, 22702, 33213, 35826, 61521, 42735, 36000, 59406, 103939, 35151, 54004, 19844, 29581, 16757, 33014, 70058, 41887, 1451, 44754, 24760, 31089, 31857, 106573, 101979, 107521, 68572, 4309, 103323, 103248, 98622, 62004, 23686, 7225, 60370, 90042, 92175, 61318, 6724, 20730, 98946, 11442, 107221, 62041, 12338, 79040, 71545, 70909, 68931, 72646, 41218, 75682, 76109, 90534, 56109, 73344, 75072, 81689, 50236, 100978, 101900, 70747, 8233, 2272, 74435, 24813, 82898, 83204, 96009, 67794, 1387, 6056, 2242, 23123, 10854, 87690, 90, 66053, 66552, 36589, 81814, 90600, 57025, 33577, 32573, 24733, 3803, 98153, 99122, 105007, 725, 84727, 75746, 34810, 90766, 22148, 22525, 36643, 55855, 21221, 99329, 71569, 63993, 21715, 61723, 4650, 25731, 45402, 56308, 87078, 78708, 41490, 68958, 102029, 61137, 6668, 104741, 59974, 63316, 93394, 27002, 80410, 13495, 59482, 103983, 35794, 105725};
        path = find_path_to_point_of_interest(789, "Shoppers Drug Mart");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(789, valid_end_intersections, path));
        CHECK(path_cost <= 7.412784627563598);
        
        valid_end_intersections = {100774, 105444, 5185, 12458, 718, 100550, 58152, 17419, 1051, 3955, 1014, 2271, 16982, 23132, 98899, 101404, 19081, 26459, 56532, 36635, 95336, 7228, 63129, 92835, 21437, 36298, 23842, 749, 56398, 19837, 16758, 36646, 85504, 99106, 1273, 71793, 27150, 103731, 33577, 98620, 24379, 6867, 10040, 91, 6861, 16222, 97865, 99358, 90569, 73350, 24563, 45674, 100978, 94112, 93349, 81128, 25725, 93140, 94713, 13280, 20232, 31108, 55867, 92435, 30989, 31437, 64642, 69786, 3633, 33434, 22151, 32066, 90578, 50517, 62040, 96035, 22508, 59185, 34721, 58665, 74521, 5458, 89809, 99298, 74729, 96829, 16762, 19422, 90111, 41495, 53494, 50353};
        path = find_path_to_point_of_interest(13617, "McDonald's");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(13617, valid_end_intersections, path));
        CHECK(path_cost <= 4.011949321583365);
        
        valid_end_intersections = {35320};
        path = find_path_to_point_of_interest(39826, "Pango");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(39826, valid_end_intersections, path));
        CHECK(path_cost <= 15.13886963103538);
        
        valid_end_intersections = {33234, 1868, 41447, 4013, 12572, 6865, 63067, 4182, 20024, 16674, 16695, 4303, 59289, 10082, 41904, 59277, 16982, 33019, 35886, 18798, 59406, 103957, 33014, 56839, 21364, 12581, 57046, 60374, 16767, 83299, 78935, 29524, 59016, 38971, 103250, 11750, 61608, 10068, 3678, 1896, 1792, 6860, 50908, 2061, 3305, 98160, 72374, 19132, 2248, 41886, 78403, 52556, 88597, 18680, 47984, 107997, 28501, 30394, 749, 62041, 16759, 6305, 71708, 67794, 16945, 70813, 88331, 94638, 87075, 12577, 1450, 26560, 50517, 3433, 92819, 5933, 1272, 94185, 24810, 884, 49119, 35236, 33477, 30558, 53003, 91411, 88593, 89809, 100644, 74058, 34613, 49443, 33048, 56243, 1862, 28335, 90858, 28635, 36679, 78526, 63217};
        path = find_path_to_point_of_interest(84955, "CIBC");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(84955, valid_end_intersections, path));
        CHECK(path_cost <= 3.378731400872689);
        
        valid_end_intersections = {59827};
        path = find_path_to_point_of_interest(86972, "Jiffy Self Storage");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(86972, valid_end_intersections, path));
        CHECK(path_cost <= 8.701278320743345);
        
        valid_end_intersections = {68361, 82921, 88674};
        path = find_path_to_point_of_interest(90183, "Dentist");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(90183, valid_end_intersections, path));
        CHECK(path_cost <= 32.36520774989595);
        
        valid_end_intersections = {105444, 12425, 14609, 18768, 5184, 2290, 41909, 1745, 58152, 87075, 4712, 15309, 16690, 12788, 33025, 7766, 2277, 36641, 21369, 1666, 2125, 23135, 3394, 15228, 20195, 1113, 1080, 71671, 101438, 33279, 72235, 102554, 54322, 95335, 31988, 26814, 96942, 101800, 74932, 43196, 8192, 36298, 23842, 8874, 96170, 41904, 28591, 28896, 9799, 1272, 2600, 21238, 59297, 6779, 45677, 92099, 68036, 81392, 105975, 106581, 1870, 95400, 96689, 54015, 44157, 60874, 72563, 61229, 20009, 84777, 79040, 102490, 90879, 6152, 47606, 53501, 1949, 60378, 2243, 6867, 5510, 11261, 16263, 90758, 70075, 44349, 20232, 1792, 5176, 71114, 98946, 1422, 51282, 35154, 13097, 14985, 97865, 5198, 1131, 3984, 41268, 76172, 75682, 2272, 4017, 75739, 31198, 32076, 95943, 1744, 77284, 23975, 28331, 82477, 105838, 106166, 2270, 50317, 33060, 74417, 90256, 104623, 30926, 82001, 58307, 61331, 99545, 5814, 96062, 10562, 96525, 6056, 45674, 79798, 4016, 70806, 11348, 67447, 78734, 78718, 69926, 82046, 25311, 26564, 10496, 90120, 40907, 42219, 96908, 55962, 25923, 71477, 33281, 44748, 24805, 70646, 108023, 33024, 58772, 81880, 84593, 60721, 58790, 18982, 94170, 63869, 95305, 23034, 22959, 96293, 35061, 35582, 22612, 39503, 26474, 7801, 9714, 89550, 34721, 67695, 86620, 97329, 16770, 79726, 50621, 50542, 41887, 83219, 106040, 99329, 15793, 5458, 98781, 22107, 99294, 100639, 101455, 36512, 42192, 69946, 19145, 1897, 7743, 92199, 25414, 1047, 4631, 79345, 45499, 82021, 6514, 23412, 100133, 1744, 1059, 53719, 100647, 4303, 74077, 79885, 1353, 107455, 56415, 5093, 22698, 35110, 97748, 79631, 727, 6668, 45124, 59967, 82274, 107639, 99904, 73443, 107650, 27011, 13495, 52477, 82678, 13027, 93607, 29584};
        path = find_path_to_point_of_interest(21548, "Tim Hortons");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(21548, valid_end_intersections, path));
        CHECK(path_cost <= 4.032169785232221);
        
        valid_end_intersections = {4013, 4103, 1896, 10078, 2258, 4183, 3943, 88675, 7849, 7387, 32553, 62307, 12857, 6229, 54004, 41886, 89207, 43893, 1790, 21729, 11454, 52556, 4641, 89488, 58760, 1422, 6868, 4017, 94142, 94123, 41902, 103578, 749, 82104, 98946, 62045, 79798, 9232, 107818, 25657, 61288, 84727, 75772, 20676, 82013, 87156, 91583, 20193, 34611, 102311, 61733, 5200, 89512, 43698, 6123, 24735, 5402, 43520, 377, 103984};
        path = find_path_to_point_of_interest(18521, "BMO Bank of Montreal");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(18521, valid_end_intersections, path));
        CHECK(path_cost <= 5.276644859615445);
        
        valid_end_intersections = {5204, 45670, 5185, 82551, 1487, 1833, 12572, 11031, 513, 6997, 63067, 97836, 4182, 727, 16674, 81174, 2259, 45089, 3340, 2292, 9236, 70897, 95463, 18670, 99114, 93480, 1078, 23113, 59300, 20194, 10869, 11016, 24460, 10077, 99992, 2955, 7359, 57768, 23035, 57420, 2142, 4320, 14601, 45640, 107820, 57809, 4756, 62134, 61721, 25555, 21033, 21437, 1219, 69668, 54322, 35151, 56405, 15076, 19848, 41888, 82161, 45499, 88579, 44755, 36643, 57025, 11621, 35124, 2277, 13491, 103732, 78869, 98642, 50657, 4297, 13280, 103325, 20697, 7374, 90859, 70714, 85313, 70080, 30545, 13547, 91, 89185, 16270, 101013, 86929, 11652, 71366, 55837, 51470, 62041, 98166, 67837, 1014, 72647, 72722, 13509, 78657, 90530, 20573, 31198, 75072, 2616, 61318, 78708, 79851, 12380, 31088, 39914, 100978, 59011, 41993, 83226, 20638, 58307, 44748, 108439, 94713, 71708, 41888, 49570, 28929, 10705, 14875, 15327, 96378, 102316, 26561, 31353, 31436, 90149, 86671, 92235, 90611, 105177, 33433, 34329, 16982, 105008, 105754, 10654, 73025, 76161, 89164, 41888, 91364, 22203, 64251, 97329, 96696, 21220, 97512, 5454, 13479, 106280, 35327, 3339, 19847, 24385, 45095, 34069, 86359, 91838, 53707, 36467, 79328, 2569, 91665, 7830, 52498, 6652, 32341, 106756, 63321, 49388, 101345, 93394, 103775, 103980, 18532, 49629, 93660};
        path = find_path_to_point_of_interest(9140, "TD Canada Trust");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(9140, valid_end_intersections, path));
        CHECK(path_cost <= 5.509199130058581);
        
        valid_end_intersections = {68361, 27859};
        path = find_path_to_point_of_interest(103682, "Animal Hospital");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(103682, valid_end_intersections, path));
        CHECK(path_cost <= 45.79181940814287);
        
        valid_end_intersections = {26675};
        path = find_path_to_point_of_interest(97609, "Jade Tree Healing Arts Centre");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(97609, valid_end_intersections, path));
        CHECK(path_cost <= 44.80030980036317);
        
        valid_end_intersections = {9236, 1450, 59286, 39981, 64274, 11808, 16263, 41888, 5709, 54367, 41907, 83189, 105651, 101900, 9390, 16771, 1451, 16576, 6865, 87076, 66167, 32569, 1722, 80267, 67618, 22239, 20668, 35412, 11642, 91364, 82021, 27134, 91582, 97220, 98466, 70504, 60527, 64450, 73649, 50713, 36288, 28635, 78502};
        path = find_path_to_point_of_interest(12519, "RBC");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(12519, valid_end_intersections, path));
        CHECK(path_cost <= 1.643418843279593);
        
        valid_end_intersections = {26579};
        path = find_path_to_point_of_interest(63719, "Kingsway Baptist Church");
        path_cost = compute_path_travel_time(path);
        CHECK(path_is_legal(63719, valid_end_intersections, path));
        CHECK(path_cost <= 39.97706228611789);
        
    } //find_path_to_point_of_interest_functionality

} //inter_poi_path_func_public
