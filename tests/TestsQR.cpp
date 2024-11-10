#include <gtest/gtest.h>

#include "../headers/Matrix.h"
#include "../headers/decomposition/QR.h"

TEST(defaultStructureQRClass, matrixConstructor) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };
    QR test(A);
    EXPECT_EQ(test.A(), A);
    Matrix<> def;
    EXPECT_TRUE(test.Q() == def);
    EXPECT_TRUE(test.R() == def);

    Matrix<> B;
    EXPECT_THROW(QR test2(B), std::runtime_error);
}

TEST(defaultStructureQRClass, copyConstructor) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };
    QR original(A);
    QR copy(original);

    EXPECT_EQ(copy.A(), original.A());
    EXPECT_EQ(copy.Q(), original.Q());
    EXPECT_EQ(copy.R(), original.R());
}

TEST(defaultStructureQRClass, moveConstructor) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };
    QR original(A);

    QR moved(std::move(original));

    EXPECT_EQ(moved.A(), A);
    EXPECT_EQ(moved.Q(), Matrix<>());
    EXPECT_EQ(moved.R(), Matrix<>());

    EXPECT_EQ(original.A(), Matrix<>());
}

TEST(defaultStructureQRClass, assignmnentOperator) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };
    Matrix<> B = {
            {5, 6},
            {7, 8}
    };

    QR qrA(A);
    QR qrB(B);

    qrB = qrA;

    EXPECT_EQ(qrB.A(), qrA.A());
    EXPECT_EQ(qrB.Q(), qrA.Q());
    EXPECT_EQ(qrB.R(), qrA.R());
}

TEST(defaultStructureQRClass, moveAssignmnentOperator) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };
    QR qrA(A);

    Matrix<> B = {
            {5, 6},
            {7, 8}
    };
    QR qrB(B);

    qrB = std::move(qrA);

    EXPECT_EQ(qrB.A(), A);
    EXPECT_EQ(qrA.A(), Matrix<>());
}

TEST(defaultStructureQRClass, equaltyOperator) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };

    QR qr1(A);
    QR qr2(A);

    EXPECT_TRUE(qr1 == qr2);

    Matrix<> B = {
            {5, 6},
            {7, 8}
    };
    QR qr3(B);

    EXPECT_FALSE(qr1 == qr3);
}

TEST(defaultStructureQRClass, inEqualtyOperator) {
    Matrix<> A = {
            {1, 2},
            {3, 4}
    };

    QR qr1(A);
    QR qr2(A);

    EXPECT_FALSE(qr1 != qr2);

    Matrix<> B = {
            {5, 6},
            {7, 8}
    };
    QR qr3(B);

    EXPECT_TRUE(qr1 != qr3);
}


TEST(QR_CGS, qrGS_part1) {
    Matrix<> A = {
            {1, 2},
            {3, 4},
            {5, 6}
    };
    QR qr(A);
    qr.qrСGS();
    
    // VolframAlpha result
    Matrix<> Q = {
            { 0.169031, 0.897085},
            { 0.507093, 0.276026},
            { 0.845154, -0.345033}
    };

    double eps = 0.00001;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_TRUE(qr.Q()(i, j) > Q(i, j) - eps && qr.Q()(i, j) < Q(i, j) + eps);
        }
    }

    // VolframAlpha result
    Matrix<> R = {
        { 5.91608, 7.43736},
        { 0.0, 0.828079}
    };

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            EXPECT_TRUE(qr.R()(i, j) > R(i, j) - eps && qr.R()(i, j) < R(i, j) + eps);
        }
    }
}

TEST(QR_CGS, qrGS_part2) {
    Matrix<> A = { 
        {1, 2, 7},
        {3, 4, 8},
        {5, 6, 5}
    };

    QR qr(A);
    qr.qrСGS();

    // VolframAlpha result
    Matrix<> Q = {
    {0.169031, 0.897085, -0.408248},
    {0.507093, 0.276026, 0.816497},
    {0.845154, -0.345033, -0.408248}
    };

    double eps = 0.00001;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_TRUE(qr.Q()(i, j) > Q(i, j) - eps && qr.Q()(i, j) < Q(i, j) + eps);
        }
    }

    // VolframAlpha result
    Matrix<> R = {
        {5.91608, 7.43736, 9.46573},
        {0, 0.828079, 6.76264},
        {0, 0, 1.63299}
    };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            EXPECT_TRUE(qr.R()(i, j) > R(i, j) - eps && qr.R()(i, j) < R(i, j) + eps);
        }
    }
}


TEST(QR_CGS, qrGS_part3) {
    // 14x19
    Matrix<> A = {
        {41,21,12,28,49,43,87,64,98,13,4,93,15,89,79,11,58,81,35},
        {49,43,64,67,64,44,20,97,84,40,21,100,73,98,17,33,19,74,3},
        {1,1,56,33,27,68,27,34,44,23,33,54,70,66,23,93,93,67,1},
        {58,16,92,63,33,41,60,73,78,17,11,31,38,35,57,73,6,45,53},
        {95,11,43,76,78,82,2,19,97,53,3,51,78,77,74,46,26,89,84},
        {15,60,55,89,74,26,14,57,22,6,28,50,56,93,51,83,7,32,43},
        {28,81,54,18,13,62,11,49,20,21,48,9,43,54,60,71,91,39,25},
        {49,77,49,83,16,8,95,26,70,16,70,6,43,13,73,11,92,84,72},
        {47,8,65,30,39,66,38,48,1,90,22,88,45,61,49,8,13,78,11},
        {24,28,35,31,47,30,92,22,54,93,59,80,25,72,56,65,67,28,69},
        {58,59,14,86,35,17,91,77,91,85,1,53,44,43,16,92,58,79,2},
        {91,26,100,14,19,55,24,11,100,34,35,62,9,58,70,69,55,67,57},
        {50,96,10,20,77,89,53,10,7,53,45,52,18,3,4,85,49,97,2},
        {95,94,28,84,78,54,14,85,60,16,44,44,44,82,41,61,21,19,100}
    };

    // volframMath result 14x14
    Matrix<> Q_volfRes = {
        { -0.191503 ,  -0.22887  ,  -0.00467081,  -0.270907 ,  -0.443727 ,  -0.0700621,  -0.130783 ,  -0.22887   ,  -0.219528 ,  -0.112099 ,  -0.270907  ,  -0.425043 ,  -0.23354  ,  -0.443727  },
        {  0.0584589,  -0.0605501,  -0.00212773,   0.182553 ,   0.409788 ,  -0.359732 ,  -0.445671 ,  -0.308233  ,   0.184104 ,  -0.0802048,  -0.130693  ,   0.279888 ,  -0.441487 ,  -0.19485   },
        {  0.149629 ,  -0.209853 ,  -0.435053  ,  -0.381121 ,   0.221868 ,  -0.33672  ,  -0.249471 ,  -0.0870578 ,  -0.234287 ,  -0.130609 ,   0.239113  ,  -0.24857  ,   0.228602 ,   0.351366  },
        { -0.0147768,  -0.144238 ,  -0.165241  ,  -0.108058 ,  -0.240406 ,  -0.424714 ,   0.357762 ,  -0.204353  ,   0.0674868,  -0.0191906,  -0.353013  ,   0.518451 ,   0.362945 ,  -0.0447527 },
        { -0.249837 ,  -0.18671  ,  -0.175376  ,   0.127003 ,  -0.191304 ,  -0.290831 ,   0.180015 ,   0.52398   ,  -0.146174 ,  -0.27072  ,   0.326441  ,   0.201297 ,  -0.430859 ,   0.0176952 },
        {  0.0189675,  -0.243539 ,   0.613546  ,  -0.0817435,   0.304851 ,  -0.329397 ,   0.347175 ,   0.00429438,   0.175899 ,  -0.248243 ,   0.164105  ,  -0.284466 ,   0.140669 ,  -0.122552  },
        {  0.494225 ,  -0.163062 ,   0.0325526 ,   0.128922 ,  -0.272237 ,  -0.263197 ,  -0.202438 ,   0.23882   ,   0.0998178,   0.50501  ,   0.269577  ,  -0.0365778,   0.135414 ,  -0.335746  },
        {  0.365755 ,   0.405427 ,  -0.0241027 ,   0.163186 ,  -0.374826 ,  -0.202184 ,   0.230239 ,  -0.410722  ,   0.133314 ,  -0.196691 ,   0.209219  ,  -0.182863 ,  -0.268275 ,   0.256756  },
        {  0.324179 ,   0.254986 ,   0.246     ,  -0.201042 ,   0.162014 ,  -0.015989 ,   0.131259 ,  -0.0136216 ,  -0.758644 ,   0.0305759,   0.00538135,   0.259212 ,  -0.124003 ,  -0.16114   },
        {  0.430838 ,  -0.27052  ,   0.0733362 ,   0.407903 ,  -0.0871544,   0.084181 ,  -0.152885 ,   0.240782  ,  -0.152479 ,  -0.426375 ,  -0.459492  ,  -0.0914308,   0.105372 ,   0.194321  },
        { -0.0334687,   0.0672932,   0.255142  ,  -0.270186 ,  -0.0495802,  -0.281814 ,  -0.0236336,   0.25804   ,   0.0706222,   0.415843 ,  -0.418194  ,  -0.111265 ,  -0.3108   ,   0.495437  },
        { -0.252468 ,  -0.145035 ,  -0.124861  ,   0.598596 ,   0.16846  ,  -0.175364 ,   0.246253 ,  -0.228042  ,  -0.368377 ,   0.388368 ,  -0.0486397 ,  -0.270375 ,   0.0268224,   0.0826    },
        { -0.0119526,  -0.560335 ,   0.324871  ,  -0.0333258,  -0.233594 ,   0.262307 ,  -0.109416 ,  -0.354998  ,  -0.093663 ,   0.106948 ,   0.275798  ,   0.297684 ,  -0.116279 ,   0.345619  },
        { -0.375196 ,   0.340939 ,   0.349914  ,   0.17624  ,  -0.254507 ,  -0.286996 ,  -0.483055 ,   0.0140855 ,  -0.173703 ,  -0.130434 ,   0.11541   ,   0.0674932,   0.365386 ,   0.101191  }
    };

    // volframMath result 14x19
    Matrix<> R_volfRes = {
        {-214.096, -151.563, -162.591, -180.48, -162.236, -168.457, -134.767, -157.766, -224.236, -133.842, -90.9219, -178.696, -136.355, -194.833, -165.781, -178.112, -132.716, -212.237, -161.545},
        {0., -137.272, -2.38396, -54.9486, -45.4648, -25.5558, -55.3159, -52.3379, 13.3013, -12.3369, -70.3682, -9.34157, -30.8267, -25.6896, -11.0419, -80.1315, -78.531, -35.9705, -11.0279},
        {0., 0., -126.963, -32.9673, -9.29065, -44.4025, -29.1683, -49.1479, -36.5067, -23.4487, -44.7625, -57.1226, -59.9819, -76.4684, -62.6028, -74.6252, -58.3741, -48.6245, -14.0597},
        {0., 0., 0., -107.102, -43.1008, 23.4194, -37.2931, -63.8389, -50.4682, -12.2152, 13.0336, -24.8316, -66.1087, -56.4408, -13.9893, -20.6259, 9.39515, -20.074, -26.5539},
        {0., 0., 0., 0., -85.4254, -72.1117, 6.20756, -16.9865, 10.4626, -38.6045, -3.13509, -93.3384, -29.9117, -75.4459, -3.65007, -40.7303, 13.2177, -36.5493, 3.65004},
        {0., 0., 0., 0., 0., 63.6701, 6.35743, 0.102204, -1.52128, 27.283, 3.3349, -1.16178, 46.303, 0.883741, 6.68274, 39.8663, 74.4966, 63.426, -26.4077},
        {0., 0., 0., 0., 0., 0., 140.966, 11.5188, 55.7435, 65.8299, 22.1608, 61.4514, -15.4077, 6.19505, 37.7884, 13.3108, 72.3384, 62.9903, 2.71693},
        {0., 0., 0., 0., 0., 0., 0., 91.0963, 20.4079, -4.46192, -29.146, 41.792, 6.38688, 48.4434, -14.1641, -7.34993, -17.4626, -11.9712, -38.3238},
        {0., 0., 0., 0., 0., 0., 0., 0., 82.1333, -37.6308, -0.535432, 9.76527, 9.73006, 38.5435, 17.8652, 29.4068, 57.4056, 14.8294, 9.11283},
        {0., 0., 0., 0., 0., 0., 0., 0., 0., -86.9186, -4.31706, -34.0665, -19.0705, -21.8682, 23.9105, -29.525, -17.3056, -4.9956, 28.1881},
        {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 45.205, 9.79206, 12.8109, 32.5572, 19.6828, -33.4063, 33.3515, -29.5464, 57.8847},
        {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., -41.1575, -3.58974, -22.4055, -2.02431, 39.1762, -14.2488, -48.4274, 34.2268},
        {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., -16.7228, 19.2865, -0.930176, 71.8251, 11.6965, -35.9401, 18.0193},
        {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., -44.6234, -70.8105, 25.4987, -13.5349, 10.5262, -43.1829}
    };


    double eps = 0.001;



    // Checking volfram result

    Matrix<> A_volfRes = Q_volfRes.transpose() * R_volfRes;
    for (int i = 0; i < A.rows_size(); ++i) {
        for (int j = 0; j < A.cols_size(); ++j) {
            EXPECT_TRUE(A_volfRes(i, j) > A(i, j) - eps && A_volfRes(i, j) < A(i, j) + eps);
        }
    }





    // Checking my result

    // compute
    QR qr(A);
    qr.qrСGS();

    // A = QR
    Matrix<> A_qr = qr.Q() * qr.R();
    for (int i = 0; i < A.rows_size(); ++i) {
        for (int j = 0; j < A.cols_size(); ++j) {
            EXPECT_TRUE(A_qr(i, j) > A(i, j) - eps && A_qr(i, j) < A(i, j) + eps);
        }
    }

    // Correct signs columns Q_volfRes for Q_computed
    Q_volfRes = Q_volfRes.transpose();
    Q_volfRes *= -1.0;


    // Additional tests

    // orthogonal Q
    size_t min_mn = std::min(A.rows_size(), A.cols_size());
    Matrix<> QtQ = qr.Q().transpose() * qr.Q();
    Matrix<> I(min_mn, min_mn);
    for (size_t i = 0; i < min_mn; ++i) {
        for (size_t j = 0; j < min_mn; ++j) {
            I(i, j) = (i == j) ? 1.0 : 0.0;
        }
    }

    for (size_t i = 0; i < QtQ.rows_size(); ++i) {
        for (size_t j = 0; j < QtQ.cols_size(); ++j) {
            EXPECT_NEAR(QtQ(i, j), I(i, j), eps) << "Orthogonality check failed at (" << i << "," << j << ")";
        }
    }

    // Upper-triangular check R
    for (size_t i = 0; i < qr.R().rows_size(); ++i) {
        for (size_t j = 0; j < qr.R().cols_size(); ++j) {
            if (j < i) {
                EXPECT_NEAR(qr.R()(i, j), 0.0, eps) << "R is not upper triangular at (" << i << "," << j << ")";
            }
        }
    }

    // Check norms Q
    for (size_t j = 0; j < qr.Q().cols_size(); ++j) {
        double norm = 0.0;
        for (size_t i = 0; i < qr.Q().rows_size(); ++i) {
            norm += qr.Q()(i, j) * qr.Q()(i, j);
        }
        norm = sqrt(norm);
        EXPECT_NEAR(norm, 1.0, eps) << "Column " << j << " of Q is not normalized.";
    }


    // Ambiguity
    
    // Adjust Q_computed column signs to match Q_ref
    for (size_t j = 0; j < Q_volfRes.cols_size(); ++j) {
        // Calculate the scalar product between columns
        double dot_product = 0.0;
        for (size_t i = 0; i < Q_volfRes.rows_size(); ++i) {
            dot_product += qr.Q()(i, j) * Q_volfRes(i, j);
        }

        // If the scalar product is negative, change the sign of the column
        if (dot_product < 0) {
            for (size_t i = 0; i < Q_volfRes.rows_size(); ++i) {
                Q_volfRes(i, j) *= -1;
            }
        }
    }

    // Comparison of elements of matrix Q
    for (size_t i = 0; i < Q_volfRes.rows_size(); ++i) {
        for (size_t j = 0; j < Q_volfRes.cols_size(); ++j) {
            EXPECT_NEAR(qr.Q()(i, j), Q_volfRes(i, j), eps) << "Mismatch at Q(" << i << "," << j << ")";
        }
    }
}

TEST(QR_CGS, qrGS_part4) {
    Matrix<> A = {
        { 2, 0, -2 ,0 ,4 ,0 ,-4, 0 },
        { 0, 0, 0, 0, 0, 2, 0, -2 },
        { -2, 0, 2, 0, -4, 0, 4, 0 },
        { 0, 0, 0, 0, 0, -2, 0, 2 },
        { 4, 0, -4, 0, 2, 0, -2, 0 },
        { 0, 2, 0, -2, 0, 0, 0, 0 },
        { -4, 0, 4, 0, -2, 0, 2, 0 },
        { 0, -2, 0, 2, 0, 0, 0, 0 }
    };

    // volframMath result
    Matrix<> Q_volfRes = {
        { -0.316228,  0. ,  0.316228,  0. ,  -0.632456,  0.      ,   0.632456, 0.       },
        {  0.      ,  0. ,  0.      ,  0. ,   0.      , -0.707107,   0.      , 0.707107 },
        { -0.948683,  0. , -0.105409,  0. ,   0.210819,  0.      ,  -0.210819, 0.       },
        {  0.      , -1. ,  0.      ,  0. ,   0.      ,  0.      ,   0.      , 0.       },
        {  0.      ,  0. , -0.942809,  0. ,  -0.235702,  0.      ,   0.235702, 0.       },
        {  0.      ,  0. ,  0.      , -1. ,   0.      ,  0.      ,   0.      , 0.       },
        {  0.      ,  0. ,  0.      ,  0. ,   0.707107,  0.      ,   0.707107, 0.       },
        {  0.      ,  0. ,  0.      ,  0. ,   0.      ,  0.707107,   0.      , 0.707107 }
    };

    // volframMath result
    Matrix<> R_volfRes{
        { -6.32456,  0.     ,  6.32456,  0.     , -5.05964,  0. ,  5.05964,  0. },
        {  0.     , -2.82843,  0.     ,  2.82843,  0.     ,  0. ,  0.     ,  0. },
        {  0.     ,  0.     ,  0.     ,  0.     , -2.52982,  0. ,  2.52982,  0. },
        {  0.     ,  0.     ,  0.     ,  0.     ,  0.     , -2. ,  0.     ,  2. },
        {  0.     ,  0.     ,  0.     ,  0.     ,  2.82843,  0. , -2.82843,  0. },
        {  0.     ,  0.     ,  0.     ,  0.     ,  0.     ,  2. ,  0.     , -2. },
        {  0.     ,  0.     ,  0.     ,  0.     ,  0.     ,  0. ,  0.     ,  0. },
        {  0.     ,  0.     ,  0.     ,  0.     ,  0.     ,  0. ,  0.     ,  0. }
    };

    double eps = 0.001;



    // Checking volfram result

    Matrix<> A_volfRes = Q_volfRes.transpose() * R_volfRes;
    for (int i = 0; i < A.rows_size(); ++i) {
        for (int j = 0; j < A.cols_size(); ++j) {
            EXPECT_TRUE(A_volfRes(i, j) > A(i, j) - eps && A_volfRes(i, j) < A(i, j) + eps);
        }
    }

    // Checking my result

    // compute
    QR qr(A);
    qr.qrСGS();

    // A = QR
    Matrix<> A_qr = qr.Q() * qr.R();
    for (int i = 0; i < A.rows_size(); ++i) {
        for (int j = 0; j < A.cols_size(); ++j) {
            EXPECT_TRUE(A_qr(i, j) > A(i, j) - eps && A_qr(i, j) < A(i, j) + eps);
        }
    }
    /*
    // Correct signs columns Q_volfRes for Q_computed
    Q_volfRes = Q_volfRes.transpose();
    Q_volfRes *= -1.0;


    // Additional tests

    // orthogonal Q
    size_t min_mn = std::min(A.rows_size(), A.cols_size());
    Matrix<> QtQ = qr.Q().transpose() * qr.Q();
    Matrix<> I(min_mn, min_mn);
    for (size_t i = 0; i < min_mn; ++i) {
        for (size_t j = 0; j < min_mn; ++j) {
            I(i, j) = (i == j) ? 1.0 : 0.0;
        }
    }

    for (size_t i = 0; i < QtQ.rows_size(); ++i) {
        for (size_t j = 0; j < QtQ.cols_size(); ++j) {
            EXPECT_NEAR(QtQ(i, j), I(i, j), eps) << "Orthogonality check failed at (" << i << "," << j << ")";
        }
    }

    // Upper-triangular check R
    for (size_t i = 0; i < qr.R().rows_size(); ++i) {
        for (size_t j = 0; j < qr.R().cols_size(); ++j) {
            if (j < i) {
                EXPECT_NEAR(qr.R()(i, j), 0.0, eps) << "R is not upper triangular at (" << i << "," << j << ")";
            }
        }
    }    

    // Check norms Q
    for (size_t j = 0; j < qr.Q().cols_size(); ++j) {
        double norm = 0.0;
        for (size_t i = 0; i < qr.Q().rows_size(); ++i) {
            norm += qr.Q()(i, j) * qr.Q()(i, j);
        }
        norm = sqrt(norm);
        EXPECT_NEAR(norm, 1.0, eps) << "Column " << j << " of Q is not normalized.";
    }


    // Ambiguity

    // Adjust Q_computed column signs to match Q_ref
    for (size_t j = 0; j < Q_volfRes.cols_size(); ++j) {
        // Calculate the scalar product between columns
        double dot_product = 0.0;
        for (size_t i = 0; i < Q_volfRes.rows_size(); ++i) {
            dot_product += qr.Q()(i, j) * Q_volfRes(i, j);
        }

        // If the scalar product is negative, change the sign of the column
        if (dot_product < 0) {
            for (size_t i = 0; i < Q_volfRes.rows_size(); ++i) {
                Q_volfRes(i, j) *= -1;
            }
        }
    }

    // Comparison of elements of matrix Q
    for (size_t i = 0; i < Q_volfRes.rows_size(); ++i) {
        for (size_t j = 0; j < Q_volfRes.cols_size(); ++j) {
            EXPECT_NEAR(qr.Q()(i, j), Q_volfRes(i, j), eps) << "Mismatch at Q(" << i << "," << j << ")";
        }
    }*/
}