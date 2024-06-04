#include "pch.h"
#include "MathCompiler.h"

bool MathCompiler::IsOpSym() {
    return (std::strchr("+-*/%^()[]", expr[pos]) != nullptr);
}

/* Символ - цифра? */
bool MathCompiler::IsDigit() {
    return (expr[pos] >= '0' && expr[pos] <= '9');
}


/* Символ - буква? */
bool MathCompiler::IsLetter() {
    return ((expr[pos] >= 'a' && expr[pos] <= 'z') || (expr[pos] >= 'A' && expr[pos] <= 'Z'));
}


/* Символ - точка? */
bool MathCompiler::IsPoint() {
    return (expr[pos] == '.');
}


MathCompiler::MathCompiler() {
    root = nullptr;
}


MathCompiler::~MathCompiler() {
    DelTree(root);
    root = nullptr;
}


/* Созать узел токена */
MathCompiler::Node* MathCompiler::CreateNode(double value_, MathCompiler::Node* left_, MathCompiler::Node* right_) {
    Node* p = new Node(value_, left_, right_);
    return p;
}


void MathCompiler::SendError(int errNum) {
    //std::cout << "Something is wrong. Number of error: " << errNum << std::endl;
    return;
}


/* Получить текущий токен */
bool MathCompiler::GetToken(void) {
    //std::cout << typeToken << ' ';
    *tokenBuff = '\0';

    // Удаляем лишние пробелы
    while (expr[pos] == ' ') {
        pos++;
    }

    // Если конец выражения:
    if (expr[pos] == '\0') {
        tokenBuff[0] = '\0';
        typeToken = CALC_END;
        return true;
    }

    // Если текущий символ - операция (в том числе скобка):
    else if (IsOpSym()) {
        tokenBuff[0] = expr[pos++];
        tokenBuff[1] = '\0';

        switch (*tokenBuff) {
        case '+':
            typeToken = OP_PLUS;
            return true;
        case '-':
            typeToken = OP_MINUS;
            return true;
        case '*':
            typeToken = OP_MULTIPLY;
            return true;
        case '/':
            typeToken = OP_DIVIDE;
            return true;
        case '%':
            typeToken = OP_PERCENT;
            return true;
        case '^':
            typeToken = OP_POWER;
            return true;
        case '[':
        case '(':
            typeToken = CALC_L_BRACKET;
            return true;
        case ']':
        case ')':
            typeToken = CALC_R_BRACKET;
            return true;
        }
    }

    // Если текущий символ - буква:
    else if (IsLetter()) {
        // Получем имя функции/переменной:
        int i = 0;
        while (IsLetter()) tokenBuff[i++] = expr[pos++];
        tokenBuff[i] = '\0';

        // Приводим всё к одному регистру:
        int len = static_cast<int>(strlen(tokenBuff));
        for (i = 0; i < len; i++) {
            if (tokenBuff[i] >= 'A' && tokenBuff[i] <= 'Z') {
                tokenBuff[i] += 'a' - 'A';
            }
        }

        if (!std::strcmp(tokenBuff, "g")) {
            typeToken = CALC_G;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "pi")) {
            typeToken = CALC_PI;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "sin")) {
            typeToken = OP_SIN;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "cos")) {
            typeToken = OP_COS;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "tg")) {
            typeToken = OP_TG;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "ctg")) {
            typeToken = OP_CTG;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "arcsin")) {
            typeToken = OP_ARCSIN;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "arccos")) {
            typeToken = OP_ARCCOS;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "arcctg")) {
            typeToken = OP_ARCCTG;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "sh")) {
            typeToken = OP_SH;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "ch")) {
            typeToken = OP_CH;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "th")) {
            typeToken = OP_TH;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "cth")) {
            typeToken = OP_CTH;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "exp")) {
            typeToken = OP_EXP;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "lg")) {
            typeToken = OP_LG;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "ln")) {
            typeToken = OP_LN;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "sqrt")) {
            typeToken = OP_SQRT;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "x")) {
            typeToken = CALC_X;
            return true;
        }
        else if (!std::strcmp(tokenBuff, "y")) {
            typeToken = CALC_Y;
            return true;
        }
        else {
            SendError(0);
        }
    }
    // Если текущий символ - цифра/десятичная дочка:
    else if (IsDigit() || IsPoint()) {
        int i = 0;
        while (IsDigit()) tokenBuff[i++] = expr[pos++];

        if (IsPoint()) {
            tokenBuff[i++] = expr[pos++];
            while (IsDigit()) tokenBuff[i++] = expr[pos++];
        }

        tokenBuff[i] = '\0';
        typeToken = CALC_NUMBER;
        return true;
    }
    // Символ - неизвестный науке символ:
    else {
        tokenBuff[0] = expr[pos++];
        tokenBuff[1] = '\0';
        SendError(1);
    }
    return false;
}


// Компилируем выражение, составляя для него синтаксическое дерево
bool MathCompiler::Compile(const char* _expr) {
    pos = 0;
    expr = _expr;
    *tokenBuff = '\0';

    // Удаляем прошлое дерево
    if (root != nullptr) {
        DelTree(root);
        root = nullptr;
    }
    // Получаем очередной символ (токен)
    GetToken();
    if (typeToken == CALC_END) {
        SendError(2);
    }

    root = LowerExpr();

    if (typeToken != CALC_END) {
        SendError(3);
    }
    return true;
}


/* Выражение низшего порядка вычисления */
MathCompiler::Node* MathCompiler::LowerExpr(void) {
    MathCompiler::Node* temp = Expr1();
    // Составляем корень дерева из слагаемых. Их может быть много, поэтому цикл - бесконечный
    while (true) {
        if (typeToken == OP_PLUS) {
            GetToken();
            // Предыдущий temp - не корень, поэтому теперь он - веточка, 
            // как и его сосед, но уже другого корня
            temp = CreateNode(OP_PLUS, temp, Expr1());
        }
        else if (typeToken == OP_MINUS) {
            GetToken();
            temp = CreateNode(OP_MINUS, temp, Expr1());
        }
        else { break; }
    }

    return temp;
}


MathCompiler::Node* MathCompiler::Expr1(void)
{
    MathCompiler::Node* temp = Expr2();

    while (true) {
        if (typeToken == OP_MULTIPLY) {
            GetToken();
            temp = CreateNode(OP_MULTIPLY, temp, Expr2());
        }
        else if (typeToken == OP_DIVIDE) {
            GetToken();
            temp = CreateNode(OP_DIVIDE, temp, Expr2());
        }
        else if (typeToken == OP_PERCENT) {
            GetToken();
            temp = CreateNode(OP_PERCENT, temp, Expr2());
        }
        else if (typeToken == OP_POWER) {
            GetToken();
            temp = CreateNode(OP_POWER, temp, Expr3());
        }
        else {
            break;
        }
    }
    return temp;
}


MathCompiler::Node* MathCompiler::Expr2(void) {
    MathCompiler::Node* temp;
    if (typeToken == OP_PLUS) {
        GetToken();
        temp = Expr3();
    }
    else if (typeToken == OP_MINUS) {
        GetToken();
        temp = CreateNode(OP_UMINUS, Expr3());
    }
    else {
        temp = Expr3();
    }
    return temp;
}

/*---------------------------------------------------------------------------*/

MathCompiler::Node* MathCompiler::Expr3(void) {
    MathCompiler::Node* temp;
    if (typeToken >= OP_SIN && typeToken <= OP_SQRT + 1) {
        temp = CreateNode(OP_SIN - OP_SIN + typeToken);
        GetToken();
        if (typeToken != CALC_L_BRACKET) {
            SendError(4);
        }
        GetToken();
        temp->left = LowerExpr();
        if (typeToken != CALC_R_BRACKET) {
            SendError(5);
        }
        GetToken();
    }
    else {
        temp = Expr4();
    }
    return temp;
}

/*---------------------------------------------------------------------------*/

MathCompiler::Node* MathCompiler::Expr4(void) {
    MathCompiler::Node* temp = nullptr;
    if (typeToken == CALC_NUMBER) {
        temp = CreateNode(static_cast<double>(atof(tokenBuff)));
        GetToken();
    }
    else if (typeToken == CALC_PI) {
        temp = CreateNode(static_cast<double>(M_PI));
        GetToken();
    }
    else if (typeToken == CALC_G) {
        temp = CreateNode(static_cast<double>(F_G));
        GetToken();
    }
    else if (typeToken == CALC_X) {
        Node* t = CreateNode(var_p);
        temp = CreateNode(CALC_X, t);
        GetToken();
    }
    else if (typeToken == CALC_Y) {
        Node* t = CreateNode(var_p_y);
        temp = CreateNode(CALC_Y, t);
        GetToken();
    }

    else if (typeToken == CALC_L_BRACKET) {
        GetToken();
        temp = LowerExpr();
        if (typeToken != CALC_R_BRACKET) {
            SendError(5);
        }
        GetToken();
    }
    else {
        SendError(6);
    }
    return temp;
}


void MathCompiler::SetVariable(double _x) {
    var_p = _x;
}

void MathCompiler::SetVariableX(double _x) {
    var_p = _x;
}

void MathCompiler::SetVariableY(double _y) {
    var_p_y = _y;
}

double MathCompiler::Evaluate(void) {
    result = CalcTree(root);
    return result;
}


double MathCompiler::GetResult() {
    return result;
}


double MathCompiler::CalcTree(MathCompiler::Node* tree) {
    static double temp;
    if (tree->left == nullptr && tree->right == nullptr) {
        return tree->value;
    }
    else {
        switch (static_cast<int>(tree->value)) {
        case OP_PLUS:
            return CalcTree(tree->left) + CalcTree(tree->right);
        case CALC_X:
            return var_p;
        case CALC_Y:
            return var_p_y;
        case OP_MINUS:
            return CalcTree(tree->left) - CalcTree(tree->right);
        case OP_MULTIPLY:
            return CalcTree(tree->left) * CalcTree(tree->right);
        case OP_DIVIDE:
            return CalcTree(tree->left) / CalcTree(tree->right);
        case OP_PERCENT:
            return static_cast<int>(CalcTree(tree->left))
                % static_cast<int>(CalcTree(tree->right));
        case OP_POWER:
            return static_cast<double>(
                pow(CalcTree(tree->left), CalcTree(tree->right))
                );
        case OP_UMINUS:
            return -CalcTree(tree->left);
        case OP_SIN:
            return sin(CalcTree(tree->left));
        case OP_COS:
            return cos(CalcTree(tree->left));
        case OP_TG:
            return tan(CalcTree(tree->left));
        case OP_CTG:
            return 1.0 / tan(CalcTree(tree->left));
        case OP_ARCSIN:
            return asin(CalcTree(tree->left));
        case OP_ARCCOS:
            return acos(CalcTree(tree->left));
        case OP_ARCTG:
            return atan(CalcTree(tree->left));
        case OP_ARCCTG:
            return M_PI / 2.0 - atan(CalcTree(tree->left));
        case OP_SH:
            temp = CalcTree(tree->left);
            return (exp(temp) - exp(-temp)) / 2.0;
        case OP_CH:
            temp = CalcTree(tree->left);
            return (exp(temp) + exp(-temp)) / 2.0;
        case OP_TH:
            temp = CalcTree(tree->left);
            return (exp(temp) - exp(-temp)) / (exp(temp) + exp(-temp));
        case OP_CTH:
            temp = CalcTree(tree->left);
            return (exp(temp) + exp(-temp)) / (exp(temp) - exp(-temp));
        case OP_EXP:
            return exp(CalcTree(tree->left));
        case OP_LG:
            return log10(CalcTree(tree->left));
        case OP_LN:
            return log(CalcTree(tree->left));
        case OP_SQRT:
            return sqrt(CalcTree(tree->left));
        case OP_IN:
            return 0;
        }
    }
}


void MathCompiler::DelTree(MathCompiler::Node* tree) {
    if (tree == nullptr) {
        return;
    }
    DelTree(tree->left);
    DelTree(tree->right);
    delete tree;
    return;
}