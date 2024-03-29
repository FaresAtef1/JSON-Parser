#include "gtest/gtest.h"
#include "main.cpp"
#include "rec_des.cpp"

TEST(JSON_Parser, valid_JSONs) {
    string json1 =  "{\"fares\":[1,2,3,4],\n"
                   " \"atef\":\"fares\"}";
    string json2 = "{\"variant\":{\"type\":\"real\",\"value\":12},\"array1d\":[{\"0\":{\"type\":"
                    "\"real\",\"value\":12}},{\"1\":{\"type\":\"real\",\"value\":12}}],\"array2d\":[{\"1\":[{\"0\":{\"type\":"
                    "\"real\","
                    "\"value\":12}},{\"1\":{\"type\":\"real\",\"value\":12222}}]}]}";
    string json3 = "{\"variant\":{\"type\":\"real\",\"value\":1234},\"array1d\":[{\"0\":{\"type\":"
                    "\"real\",\"value\":123334}},{\"1\":{\"type\":\"real\",\"value\":12323234}},{\"2\":{\"type\":"
                    "\"real\",\"value\":1234}}],\"array2d\":[{\"1\":[{\"0\":{\"type\":\"real\",\"value\":1231114}},{\"1\":{\"type\":"
                    "\"real\",\"value\":9934}},{\"2\":{\"type\":\"real\",\"value\":123767224}}]},{\"2\":[{\"0\":{\"type\":"
                    "\"real\",\"value\":12899834}},{\"1\":{\"type\":\"real\",\"value\":12389324}},{\"2\":{\"type\":"
                    "\"real\",\"value\":12349954}}]}]}";
    string json4 =  "[]";
    string json5 =  "12";
    
    Parser parser1(json1);
    Rec_Parser parser2 (json1);

    ASSERT_TRUE(parser1.ParseJSON());
    ASSERT_TRUE(parser2.ParseJSON());
    parser1.ChangeIn(json2);
    parser2.ChangeIn(json2);
    ASSERT_TRUE(parser1.ParseJSON());
    ASSERT_TRUE(parser2.ParseJSON());
    parser1.ChangeIn(json3);
    parser2.ChangeIn(json3);
    ASSERT_TRUE(parser1.ParseJSON());
    ASSERT_TRUE(parser2.ParseJSON());
    parser1.ChangeIn(json4);
    parser2.ChangeIn(json4);
    ASSERT_TRUE(parser1.ParseJSON());
    ASSERT_TRUE(parser2.ParseJSON());
    parser1.ChangeIn(json5);
    parser2.ChangeIn(json5);
    ASSERT_TRUE(parser1.ParseJSON());
    ASSERT_TRUE(parser2.ParseJSON());
}

TEST(JSON_Parser, invalid_JSONs) {
    string json1 =  "{\"fares\":[1,2,3,4],\n"
                   " \"atef\":\"fares\"";
    string json2 = "{\"variant\":{\"type\":\"real\",\"value\":12},\"array1d\":[{\"0\":{\"type\":"
                    "\"real\",\"value\":12},{\"1\":{\"type\":\"real\",\"value\":12}}],\"array2d\":[{\"1\":[{\"0\":{\"type\":"
                    "\"real\","
                    "\"value\":12}},{\"1\":{\"type\":\"real\",\"value\":12222}}}]}";
    string json3 = "{\"variant\":{\"type\":\"real\",\"value\":1234},\"array1d\":[{\"0\":{\"type\":"
                    "\"real\",\"value\":123334}},{\"1\":{\"type\":\"real\",\"value\":12323234}},{\"2\":{\"type\":"
                    "\"real\",\"value\":1234}}],\"array2d\":[{\"1\":[{\"0\":{\"type\":\"real\",\"value\":1231114}},{\"1\":{\"type\":"
                    "\"real\",\"value\"9934}},{\"2\":{\"type\":\"real\",\"value\":123767224}}]},{\"2\":[{\"0\":{\"type\":"
                    "\"real\",\"value\":12899834}},{\"1\":{\"type\":\"real\",\"value\":12389324}},{\"2\":{\"type\":"
                    "\"real\",\"value\":12349954}}]}]}";
    string json4 =  "[,]";
    string json5 =  "[1,2,3";
    
    Parser parser1(json1);
    Rec_Parser parser2 (json1);

    ASSERT_FALSE(parser1.ParseJSON());
    ASSERT_FALSE(parser2.ParseJSON());
    parser1.ChangeIn(json2);
    parser2.ChangeIn(json2);
    ASSERT_FALSE(parser1.ParseJSON());
    ASSERT_FALSE(parser2.ParseJSON());
    parser1.ChangeIn(json3);
    parser2.ChangeIn(json3);
    ASSERT_FALSE(parser1.ParseJSON());
    ASSERT_FALSE(parser2.ParseJSON());
    parser1.ChangeIn(json4);
    parser2.ChangeIn(json4);
    ASSERT_FALSE(parser1.ParseJSON());
    ASSERT_FALSE(parser2.ParseJSON());
    parser1.ChangeIn(json5);
    parser2.ChangeIn(json5);
    ASSERT_FALSE(parser1.ParseJSON());
    ASSERT_FALSE(parser2.ParseJSON());
}
