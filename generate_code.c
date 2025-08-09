/*���t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "generate_code.h"

/*���p�t�@�C���̃w�b�_*/
/*****************************************************************************************/
#include "error.h"
#include "parsa.h"
#include "printout.h"
#include "stackflame.h"
#include "identify.h"

#define BYTESIZE_BUFFER 256
#define BYTESIZE_RTS 8

/*�ϐ�*/
/*****************************************************************************************/
static int label_begin;
static int label_else;
static int label_end;

int global_bytesize_push_or_pop = 0;

char* register_arguments[4] = {"rcx","rdx","r8","r9"};

/*����J�֐��F*/
/*****************************************************************************************/
void compile_function_declaration(Node* node)
{
    int stack_current = BYTESIZE_RTS; //rts��
    char buffer[BYTESIZE_BUFFER];

    Function* function = identify_function_from_string(node->name_function);

    //�֐����x��
    sprintf_s(buffer, BYTESIZE_BUFFER, "\n%s:", node->name_function);
    printout(buffer);

    //rbp�v�b�V��
    push_rbp();
    stack_current += 8;

    if (function != NULL)
    {

        //�����ƃ��[�J���ϐ��m��
        if (function->list_arguments_or_local_variables != NULL)
        {
            stack_current += function->list_arguments_or_local_variables->offset;
        }

        if (stack_current % 16 != 0)
        {
            stack_current += 16 - (stack_current % 16);
        }

        function->stack_flame = stack_current;

        printout("  mov rbp, rsp");
        sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rsp, %d\t\t#�X�^�b�N�g�b�v", stack_current - 16);
        printout(buffer);

        //�֐��̈������i�[
        for (int i = 0; i < function->count_arguments; i++)
        {
            printout("  mov rax, rbp");
            sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rax, %d", BYTESIZE_VARIABLE * (i + 1));
            printout(buffer);
            sprintf_s(buffer, BYTESIZE_BUFFER, "  mov [rax], %s\t#�����i�[", register_arguments[function->count_arguments - i - 1]);
            printout(buffer);
        }

        for (int i = 0; function->code[i]; i++)
        {
            compile_code(function->code[i]);
        }
    }
    global_bytesize_push_or_pop = 0;
}

void compile_function_call(Node* node)
{
    char buffer[BYTESIZE_BUFFER];
    int alignment = 0;

    Function* function_print = identify_function_from_string(node->name_function);

    if (function_print == NULL)
    {
        error("�֐���������܂���");
    }

    if (node->arguments[0] != NULL)
    {
        for (int i = 0; i < node->count_arguments; i++)
        {
            compile_code(node->arguments[i]);
        }
    }

    for (int i = 0; i < node->count_arguments; i++)
    {
        sprintf_s(buffer, BYTESIZE_BUFFER, "%s", register_arguments[node->count_arguments - i - 1]);
        pop(buffer);
    }

    if (global_bytesize_push_or_pop % 16 != 0)
    {
        alignment = 16 - (global_bytesize_push_or_pop % 16);
    }

    sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rsp, %d\n  call %s\n  add rsp, %d", alignment, node->name_function, alignment);
    printout(buffer);

    push("rax");
}

void compile_argument_or_variable(Node* node) 
{
    char buffer[BYTESIZE_BUFFER];
    if (node->kind != NODE_ARGUMENT_OR_VARIABLE)
    {
        error("����̍��Ӓl���ϐ��ł͂���܂���");
    }
    printout("  mov rax, rbp");
    sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rax, %d", node->offset_argument_or_local_variable);
    printout(buffer);
    push("rax");
    pop("rax");
    printout("  mov rax, [rax]");
    push("rax");
}

void compile_number(Node* node)
{
    char  buf[256];
    sprintf_s(buf, BYTESIZE_BUFFER, "%d", node->value_number);
    push(buf);
}

void compile_dereference(Node* node)
{
    compile_code(node->left_hand_side);
    pop("rax");
    printout("  mov rax, [rax]");
    push("rax");
}

void compile_return(Node* node)
{
    compile_code(node->left_hand_side);
    pop("rax");
    printout("  mov rsp, rbp");
    pop_rbp();
    ret();
}

void compile_assign(Node* node)
{
    char buffer[BYTESIZE_BUFFER];
    if (node->left_hand_side->kind != NODE_ARGUMENT_OR_VARIABLE)
    {
        error("����̍��Ӓl���ϐ��ł͂���܂���");
    }
    printout("  mov rax, rbp");
    sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rax, %d", node->left_hand_side->offset_argument_or_local_variable);
    printout(buffer);
    push("rax");
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  mov [rax], rdi");
    push("rdi");
}

void compile_block(Node* node)
{
    for (int i = 0; node->block[i]; i++)
    {
        compile_code(node->block[i]);
    }
}

void compile_address(Node* node)
{
    char buffer[BYTESIZE_BUFFER];
    if (node->left_hand_side->kind != NODE_ARGUMENT_OR_VARIABLE)
    {
        error("����̍��Ӓl���ϐ��ł͂���܂���");
    }
    printout("  mov rax, rbp");
    sprintf_s(buffer, BYTESIZE_BUFFER, "  sub rax, %d", node->left_hand_side->offset_argument_or_local_variable);
    printout(buffer);
    push("rax");
}

void compile_less_than_or_equal(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  cmp rax, rdi");
    printout("  setle al");
    printout("  movzb rax, al");
    push("rax");
}

void compile_add(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  add rax, rdi");
    push("rax");
}

void compile_subtract(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  sub rax, rdi");
    push("rax");
}

void compile_less_than(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  cmp rax, rdi");
    printout("  setl al");
    printout("  movzb rax, al");
    push("rax");
}

void compile_not_equal(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  cmp rax, rdi");
    printout("  setne al");
    printout("  movzb rax, al");
    push("rax");
}

void compile_equal(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  cmp rax, rdi");
    printout("  sete al");
    printout("  movzb rax, al");
    push("rax");
}

void compile_division(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  cqo");
    printout("  idiv rdi");
    push("rax");
}

void compile_multiplication(Node* node)
{
    compile_code(node->left_hand_side);
    compile_code(node->right_hand_side);
    pop("rdi");
    pop("rax");
    printout("  imul rax, rdi");
    push("rax");
}

void compile_if(Node* node)
{
    int label_end_local = label_end;
    int label_else_local = label_else;

    label_end++;
    compile_code(node->left_hand_side);
    pop("rax");
    printout("  cmp rax, 0");

    if (node->right_hand_side->right_hand_side == NULL)
    {
        printout_jmplabel("je", ".Lend", label_end_local);
        compile_code(node->right_hand_side->left_hand_side);
    }
    else
    {
        label_else++;
        printout_jmplabel("je", ".Lelse", label_else_local);
        compile_code(node->right_hand_side->left_hand_side);
        printout_jmplabel("jmp", ".Lend", label_end_local);
        printout_label(".Lelse", label_else_local);
        compile_code(node->right_hand_side->right_hand_side->left_hand_side);
    }
    printout_label(".Lend", label_end_local);
}

void compile_while(Node* node)
{
    int label_begin_local = label_begin;
    int label_end_local = label_end;
    label_begin++;
    label_end++;
    printout_label(".Lbegin", label_begin_local);
    compile_code(node->left_hand_side);
    pop("rax");
    printout("  cmp rax, 0");
    printout_jmplabel("je", ".Lend", label_end_local);
    compile_code(node->right_hand_side);
    printout_jmplabel("jmp", ".Lbegin", label_begin_local);
    printout_label(".Lend", label_end_local);
}

void compile_for(Node* node)
{
    int label_begin_local = label_begin;
    int label_end_local = label_end;

    //for(A;B;C)D
    label_begin++;
    label_end++;
    if (node->left_hand_side != NULL)//A
    {
        compile_code(node->left_hand_side);
    }
    printout_label(".Lbegin", label_begin_local);
    if (node->right_hand_side->left_hand_side != NULL)//B
    {
        compile_code(node->right_hand_side->left_hand_side);
    }
    pop("rax");
    printout("  cmp rax, 0");
    printout_jmplabel("je", ".Lend", label_end_local);
    compile_code(node->right_hand_side->right_hand_side->right_hand_side);//D
    if (node->right_hand_side->right_hand_side->left_hand_side != NULL)//C
    {
        compile_code(node->right_hand_side->right_hand_side->left_hand_side);
    }
    printout_jmplabel("jmp", ".Lbegin", label_begin_local);
    printout_label(".Lend", label_end_local);
}

// �֐��̌^���`
typedef void (*compiler_function)(Node*);

// �R���p�C���֐��̔z����`
compiler_function compilers[] = {
    [NODE_FUNCTION_DECLARATION] = compile_function_declaration,
    [NODE_FUNCTION_CALL] = compile_function_call,
    [NODE_NUMBER] = compile_number,
    [NODE_ARGUMENT_OR_VARIABLE] = compile_argument_or_variable,
    [NODE_ASSIGN] = compile_assign,
    [NODE_RETURN] = compile_return,
    [NODE_IF] = compile_if,
    [NODE_WHILE] = compile_while,
    [NODE_FOR] = compile_for,
    [NODE_BLOCK] = compile_block,
    [NODE_ADDRESS] = compile_address,
    [NODE_DEREFERENCE] = compile_dereference,
    [NODE_ADD] = compile_add,
    [NODE_SUBTRACT] = compile_subtract,
    [NODE_MULTIPLICATION] = compile_multiplication,
    [NODE_DIVISION] = compile_division,
    [NODE_EQUAL] = compile_equal,
    [NODE_NOT_EQUAL] = compile_not_equal,
    [NODE_LESS_THAN] = compile_less_than,
    [NODE_LESS_THAN_OR_EQUAL] = compile_less_than_or_equal,
};

void compile_code(Node* node)
{
    if (compilers[node->kind] == NULL)
    {
        error("�֐��|�C���^�����݂��Ă��܂���");
    }

    compilers[node->kind](node);
}





