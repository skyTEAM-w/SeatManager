package com.seatmanager.version0;

import java.io.*;
import java.util.*;

public class SeatManagerImp {

    public static void showUI() {
        System.out.println("          座位表随机生成系统V1.8.0(Java version)");
        System.out.println("----------***********************************----------");
        System.out.println("V1.8.0 Java预览版：\n采用Java构建项目，\n采用了与v1.X(Cpp version)版本完全不同的算法");
        System.out.println("文件的读入形式与上一版本相同");
        System.out.println("----------***********************************----------");
        System.out.println("1.开始生成座位表\n2.查看已经生成的座位表\n3.清空所有的座位表\n0.退出系统");
    }

    public static void creatTable() throws IOException {
        File file = new File(".\\读入文件.txt");
        if (!file.exists()) {
            System.out.println("文件不存在！");
        } else {
            BufferedReader fileInput = new BufferedReader(new FileReader(".\\读入文件.txt"));
            Scanner consoleInput = new Scanner(System.in);
            System.out.print("请输入所排的列数：");
            int Row = consoleInput.nextInt();
            System.out.print("准备生成的座位表数量：");
            int Number = consoleInput.nextInt();
            System.out.println("开始生成......");

            //座位表生成实现区
            //1.读入学生名单
            String line;
            int number = 0;
            Map<Integer, Student> studentMap = new HashMap<Integer, Student>();
            ArrayList<Integer> studentArraylist = new ArrayList<>();
            while ((line = fileInput.readLine()) != null) {
                String[] strings = line.split("\t");
                Student student = new Student(strings[1], strings[0]);
                studentMap.put(number, student);
                studentArraylist.add(number++);
            }
            System.out.println("读入完成，共" + number + "人");

            //2.按行数进行生成
            StringBuilder seatTableBuilder = new StringBuilder();
            for (int i = 0; i < Number; i++) {
                Collections.shuffle(studentArraylist);
                int Line = 1;
                for (Integer integer : studentArraylist) {
                    seatTableBuilder.append(studentMap.get(integer).getName());
                    if (Line % Row == 0) {
                        seatTableBuilder.append("\n");
                    } else {
                        seatTableBuilder.append("\t");
                    }
                    Line ++;
                }
                seatTableBuilder.append("\n").append("♦");;
            }

            String[] tempTables = seatTableBuilder.toString().split("♦");

            for (int i = 0; i < tempTables.length; i++) {
                System.out.println("----------************第" + (i + 1) + "个表***********----------");
                System.out.println(tempTables[i]);
            }

        }
    }
}
