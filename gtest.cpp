#include "gtest/gtest.h"
#include "main.cpp"

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
    
    Parser parser(json1);

    ASSERT_TRUE(parser.ParseJSON());
    parser.ChangeIn(json2);
    ASSERT_TRUE(parser.ParseJSON());
    parser.ChangeIn(json3);
    ASSERT_TRUE(parser.ParseJSON());
    parser.ChangeIn(json4);
    ASSERT_TRUE(parser.ParseJSON());
    parser.ChangeIn(json5);
    ASSERT_TRUE(parser.ParseJSON());
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
    
    Parser parser(json1);

    ASSERT_FALSE(parser.ParseJSON());
    parser.ChangeIn(json2);
    ASSERT_FALSE(parser.ParseJSON());
    parser.ChangeIn(json3);
    ASSERT_FALSE(parser.ParseJSON());
    parser.ChangeIn(json4);
    ASSERT_FALSE(parser.ParseJSON());
    parser.ChangeIn(json5);
    ASSERT_FALSE(parser.ParseJSON());
}
