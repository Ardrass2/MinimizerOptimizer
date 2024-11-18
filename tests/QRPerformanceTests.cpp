#include <gtest/gtest.h>

#include "../headers/Matrix.h"
#include "../headers/decomposition/QR.h"

TEST(QRPerformance, qr1) {
    Matrix<> BIG = {
            {   637.138506935875398085045162588358,   536.823930986501750339812133461237,   519.382732515572001830150838941336,   590.872029892296723119216039776802,   394.323469912703444606449920684099,   793.683023807467748156341258436441,   167.552243378654594607723993249238,   124.920182228430633131210925057530,   480.935871254309233790991129353642,   258.906306103930660356127191334963 },
            {   381.341852668768410694610793143511,   812.837925034921113365271594375372,   292.183866698670044570462778210640,   261.588716954129210989776765927672,    89.770240058288521822760230861604,   829.445469331774802412837743759155,   995.247557440332457190379500389099,   294.873160431668111414182931184769,   568.350230582632434561674017459154,   301.589172013348445489100413396955 },
            {    60.648811525828691060269193258137,   617.254910538917215490073431283236,   662.111113843894372621434740722179,   914.274301878488927286525722593069,   726.466227178108965745195746421814,   558.265808995794600377848837524652,    64.919418250298022599054093006998,   855.477472448080220601696055382490,   654.639583679973043217614758759737,   946.200774218220772127097006887197 },
            {   135.650673668994841136736795306206,   505.440009390342652295657899230719,   956.533268633990360285679344087839,   796.286210863391033853986300528049,   919.832151682080052523815538734198,   800.281781262109234376111999154091,   402.536929729960377244424307718873,   263.792757751944407118571689352393,   294.238460583962819328007753938437,   312.422325288427600753493607044220 },
            {   823.496710845537563727702945470810,   142.658733941302585890298360027373,    95.273669527855432193064189050347,   960.264280465322599411592818796635,   845.310290770948654426319990307093,   773.596750928579467654344625771046,   524.368914134789406489289831370115,   973.375549805477703557698987424374,   923.108285531196884221571963280439,   557.521542431254488292324822396040 },
            {   640.297382916897277027601376175880,   615.862674956983937590848654508591,   911.628647274526429100660607218742,   269.678390831460319532197900116444,   796.365465162596478876366745680571,   333.915522283895370492246001958847,    48.315511256469449108408298343420,   711.463918103855007757374551147223,   255.024424831365820409700972959399,   876.738804534839459847717080265284 },
            {   964.459532640623933730239514261484,   260.513120411613215310353552922606,   509.599609807695969720953144133091,   521.403742662983859190717339515686,   675.369580903049723019648808985949,   201.077008438219138497515814378858,   525.590067183716428189654834568501,   180.876685775335175776490359567106,   879.279728650102924802922643721104,   811.953816177514568153128493577242 },
            {    23.739212795570825420554683660157,   636.020393742053784080781042575836,   145.195316385496028033230686560273,   998.429514706915483657212462276220,   342.228249938223598292097449302673,   462.324945282971100368740735575557,   110.162262597880271641770377755165,   102.520912173532366296058171428740,   243.807573012508157717093126848340,   718.766916928603563974320422858000 },
            {   728.880696683767723698110785335302,   552.265430072250524062837939709425,   119.756893032778108931779570411891,   263.194677472224213943263748660684,   118.634915582341420758893946185708,    69.765457040208460171015758533031,   581.375429985977461910806596279144,   906.898832123712736574816517531872,    30.679223165528910044486110564321,   886.148699582979475053434725850821 },
            {   671.444839502739796444075182080269,   936.056398256568286342371720820665,   527.664021169574766645382624119520,   470.611369004854850572883151471615,     2.688426549755226879767633363372,   879.410247874370497811469249427319,   896.084118621328798326430842280388,   256.470860647476115445897448807955,   405.539456746525331709563033655286,   772.141898391451718453026842325926 },
    };

    double eps = 1e-12;

    QR qr(BIG);
    qr.qrIMGS();

    Matrix<> BIG_qr = qr.Q() * qr.R();
    for (int i = 0; i < BIG.rows_size(); ++i) {
        for (int j = 0; j < BIG.cols_size(); ++j) {
            EXPECT_TRUE(BIG_qr(i, j) > BIG(i, j) - eps && BIG_qr(i, j) < BIG(i, j) + eps);
        }
    }
}