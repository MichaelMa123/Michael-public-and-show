def arithmetic_arranger(problems, show_answers=False):
    # lines_1=[]
    # lines_2=[]
    # for char in problems:
    #     line_1=''
    #     line_2_start=True
    #     line_2=''
    #     for char in char:
    #         if char. isnumeric() & line_2_start:
    #             line_1+=char
    #             print(line_1)
    #         elif not char. isnumeric() and line_2_start:
    #             lines_1.append(line_1)
    #             line_2_start=False
    #         elif char. isnumeric() and not line_2_start:
    #             line_2+=char
    #             print(line_2)
    #     lines_2.append(line_2)
    #     if len(line_1)>4 or len(line_2)>4:
    #         raise ValueError('Error: Numbers cannot be more than four digits.')
    # print(lines_1)
    # print(lines_2)
    # return problems
    lines=[]
    for char in problems:
        lines+=char.split()
        print(f"{lines}")
    if len(lines)>15:
        return 'Error: Too many problems.'
    # i=0
    # j=0
    # k=0
    # LINE1=''
    # LINE2=''
    # operater=''
    # Line3=''
    # line1_len=0
    # line2_len=0

    # for char in lines:
    #     #print(i)
    #     if (i-1)%3==0 and (char!= '+' and char!='-'):
    #         print("Error: Operator must be '+' or '-'.")
    #     if (i-1)%3==0:
    #         operater=char
    #     if (i+3)%3==0:
    #         offset=5-len(char)
    #         printer=''
    #         if j==0:
    #             printer = ' ' * (offset+1)
    #         else:
    #             printer = ' ' * (offset+3)
    #         LINE1+=F"{printer}{char}"
    #         print (LINE1)
    #         line1_len=len(char)
    #         j+=1
    #     if (i+1)%3==0:
    #         offset=5-len(char)
    #         printer=''
    #         if k==0:
    #             printer = operater+' ' * (offset)
    #         else:
    #             printer = ' '*2+operater+' ' * (offset)
    #         LINE2+=F"{printer}{char}"
    #         print (LINE2)
    #         line2_len=len(char)
    #         k+=1
    #     i+=1
    line1=lines[0::3]
    line2=lines[2::3]
    operater=lines[1::3]
    i=0
    line_1=''
    line_2=''
    dash_1=''
    answer_1=''
    for char in operater:
        offset=0
        dashes=0
        answer=0
        if (char!= '+' and char!='-'):
            return "Error: Operator must be '+' or '-'."
        if len(line1[i])>4 or len(line2[i])>4:
            return 'Error: Numbers cannot be more than four digits.'
        if not line1[i].isnumeric() or not line2[i].isnumeric():
            return 'Error: Numbers must only contain digits.'
        if(char== '+'):
            answer=int(line1[i])+int(line2[i])
        else:
            answer=int(line1[i])-int(line2[i])
        if len(line1[i])>len(line2[i]):
            offset=1+len(line1[i])
            dashes=len(line1[i])+2
        else:
            offset=1+len(line2[i])
            dashes=len(line2[i])+2
        if(i==0):
            line_1+=' '*(offset-len(line1[i])+1)+line1[i]
            line_2+=char+' '*(offset-len(line2[i]))+line2[i]
            dash_1+='-'*dashes
            answer_1+=' '*(offset-len(str(answer))+1)+str(answer)
        else:
            line_1+=' '*(offset-len(line1[i])+5)+line1[i]
            line_2+=' '*4+char+' '*(offset-len(line2[i]))+line2[i]
            dash_1+=' '*4+'-'*dashes
            answer_1+=' '*4+' '*(offset-len(str(answer))+1)+str(answer)
        i+=1
    if not show_answers:
        return f"{line_1}\n{line_2}\n{dash_1}"
    else:
        return f"{line_1}\n{line_2}\n{dash_1}\n{answer_1}"

        

print(f'\n{arithmetic_arranger(["3 + 855", "988 + 40"], True)}')
