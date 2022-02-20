import random
import xlwt
import xlrd
import os

file_path = '.\\读入文件.txt'
temp_table = []
workbook = xlwt.Workbook(encoding='utf-8', style_compression=0)


def show_ui():
    print("座位表随机生成系统V1.8.0(Python version)")
    print("-------------------------------------")
    print("1.开始生成座位表\n2.查看已经生成的座位表\n3.清空所有的座位表\n0.退出系统")


def make_table():
    file = open(file_path, 'r')
    student_list = file.read().split('\n')
    number = 1

    stu_dic = {}
    stu_arr = []
    for student in student_list:
        stu_dic.update({number: student})
        stu_arr.append(number)
        number += 1

    row = int(input('Row:'))
    number_of_tables = int(input('Number of tables:'))

    for i in range(0, number_of_tables):
        random.shuffle(stu_arr)
        table_org = [stu_dic.get(key) for key in stu_arr]
        table_item = []
        table_buf = []
        j = 1
        for temp in table_org:
            if j % row != 0:
                table_buf.append(temp)
            else:
                table_buf.append(temp)
                table_item.append(list(table_buf))
                while len(table_buf) != 0:
                    table_buf.pop()
            j += 1

        if len(table_buf) > 0:
            table_item.append(list(table_buf))

        print('----------{}----------'.format(i + 1))
        for col in table_item:
            print(col)

        temp_table.append(list(table_item))

        save_data(datalist=table_item, save_path='.\\seat_tables.xls', index=i)
        print('文件已保存至%s' % '.\\seat_tables.xls')


def save_data(datalist, save_path, index) -> None:
    worksheet = workbook.add_sheet('seat_table' + str(index + 1), False)
    i = 0
    for col in datalist:
        j = 0
        for item in col:
            worksheet.write(i, j, item)
            j += 1
        i += 1
    workbook.save(save_path)


def show_table():
    if os.path.exists("seat_tables.xls") and len(temp_table) == 0:
        workbook_open = xlrd.open_workbook('seat_tables.xls', encoding_override='utf-8')
        all_sheet = workbook_open.sheets()
        for sheet in all_sheet:
            table_buf = []
            print("----------{0}----------".format(sheet.name))
            for each_row in range(sheet.nrows):
                print(sheet.row_values(each_row))
                table_buf.append(sheet.row_values(each_row))
            temp_table.append(list(table_buf))
    elif len(temp_table) >= 0:
        i = 1
        for data in temp_table:
            print('----------{}----------'.format(i))
            for row in data:
                print(row)
            i += 1
    else:
        print('无已生成的座位表')


def delete_table():
    sel = str(input('是否确认删除：\ny:确认\nn:放弃\n'))
    if sel == 'y':
        if os.path.exists('seat_tables.xls') or len(temp_table) > 0:
            if os.path.exists('seat_tables.xls'):
                os.remove('seat_tables.xls')
                print('seat_tables.xls已删除')
            if len(temp_table) > 0:
                temp_table.clear()
                print('座位表缓存已删除')
        else:
            print('无需要删除的座位表')


if __name__ == '__main__':
    is_exit = False

    while not is_exit:
        show_ui()
        select = int(input())
        if select == 0:
            is_exit = True
        elif select == 1:
            make_table()
        elif select == 2:
            show_table()
        elif select == 3:
            delete_table()
