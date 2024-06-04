#pragma once


struct Node {
    double value;
    Node* left;
    Node* right;
    Node(
        double _value = 0.0,
        Node* _left = nullptr,
        Node* _right = nullptr
    ) {
        value = _value;
        left = _left;
        right = _right;
    }
};

class MathCompiler
{
private:
    const double M_PI = 3.1415926535897932384626433832795;
    const double F_G = 9.81;
    const double M_E = 2.71828182845904523536;

    enum Ops {
        CALC_END = -1,
        CALC_L_BRACKET = -2,
        CALC_R_BRACKET = -3,
        CALC_NUMBER = -4,
        OP_PLUS = 0,
        OP_MINUS,
        OP_MULTIPLY,
        OP_DIVIDE,
        OP_PERCENT,
        OP_POWER,
        OP_UMINUS,

        OP_SIN,
        OP_COS,
        OP_TG,
        OP_CTG,
        OP_ARCSIN,
        OP_ARCCOS,
        OP_ARCTG,
        OP_ARCCTG,
        OP_SH,
        OP_CH,
        OP_TH,
        OP_CTH,
        OP_EXP,
        OP_LG,
        OP_LN,
        OP_SQRT,
        OP_IN,
        CALC_PI,
        CALC_G,
        CALC_E,
        CALC_X,
        CALC_Y
    };

    struct Node {
        double value;
        Node* left;
        Node* right;
        Node(
            double _value = 0.0,
            Node* _left = nullptr,
            Node* _right = nullptr
        ) {
            value = _value;
            left = _left;
            right = _right;
        }
    };

    Node* root;
    const char* expr;
    char tokenBuff[80];
    int typeToken;
    int pos;
    double result = 0.0;
    double var_p = 0.0;
    double var_p_y = 0.0;


private:

    Node* CreateNode(
        double _value = 0.0,
        Node* _left = nullptr,
        Node* _right = nullptr
    );

    Node* LowerExpr(void);

    Node* Expr1(void);

    Node* Expr2(void);

    Node* Expr3(void);

    Node* Expr4(void);

    bool GetToken(void);

    bool IsOpSym(void);
    bool IsLetter(void);
    bool IsDigit(void);
    bool IsPoint(void);

    double CalcTree(Node* tree);

    void  DelTree(Node* tree);

    void SendError(int errNum);

public:
    MathCompiler();
    ~MathCompiler();

    bool Compile(const char* expr);

    double Evaluate();

    double GetResult(void);

    void SetVariable(double _x);

    void SetVariableX(double _x);

    void SetVariableY(double _y);

};

