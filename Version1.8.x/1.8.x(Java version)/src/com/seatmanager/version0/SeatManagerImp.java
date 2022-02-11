package com.seatmanager.version0;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.regex.Pattern;

public class SeatManagerImp {

    public static void showUI() {
        System.out.println("          座位表随机生成系统V1.8.0(Java version)");
        System.out.println("----------***********************************----------");
        System.out.println("V1.8.0 Java预览版：\n采用Java构建项目，\n采用了与v1.7.2(Cpp version)版本完全不同的算法");
        System.out.println("文件的读入形式与上一版本相同");
        System.out.println("----------***********************************----------");
        System.out.println("1.开始生成座位表\n2.查看已经生成的座位表\n3.清空所有的座位表\n0.退出系统");
    }

    public static void creatTable() throws IOException {
        File file = new File(".\\读入文件.txt");
        if (!file.exists()) {
            System.out.println("文件不存在！");
        } else {
            BufferedReader fileInput = new BufferedReader(new FileReader(".\\读入文件.txt"));   //输入缓冲流
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
            Map<Integer, Student> studentMap = new HashMap<>(); //学生名单映射关系
            ArrayList<Integer> studentArraylist = new ArrayList<>();    //映射值

            while ((line = fileInput.readLine()) != null) {
                String[] strings = line.split("\t");
                Student student = new Student(strings[1], strings[0]);
                studentMap.put(number, student);
                studentArraylist.add(number++);
            }
            System.out.println("读入完成，共" + number + "人");
            fileInput.close();

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
                seatTableBuilder.append("\n").append("♦");
            }

            String[] tempTables = seatTableBuilder.toString().split("♦");

            for (int i = 0; i < tempTables.length; i++) {
                System.out.println("----------************第" + (i + 1) + "个表***********----------");
                System.out.println(tempTables[i]);
            }

            //3.保存座位表
            System.out.println("预览输出完成！请查看\n1.全部保存\n2.选择部分保存\n0.放弃所有");
            BufferedReader consoleInputBuf = new BufferedReader(new InputStreamReader(System.in));
            switch (consoleInput.nextInt()) {
                case 0 -> System.out.println("已放弃所有生成的座位表！");
                case 1 -> saveTable(tempTables);
                case 2 -> {
                    System.out.println("请输入你要保存的文件编号(以空格分开)：");
                    String tempInput = consoleInputBuf.readLine();
                    TreeSet<Integer> saveIndex = new TreeSet<>();
                    String[] stringsTemp = tempInput.split(" ");
                    for (String s : stringsTemp) {
                        if (Integer.parseInt(s) > Number) {
                            continue;
                        }
                        saveIndex.add(Integer.parseInt(s));
                    }
                    saveTable(tempTables, saveIndex);
//                    consoleInputBuf.close();
                }
            }
            System.out.println("输入回车退出...");
            consoleInputBuf.readLine();
        }
    }

    public static void showTable() throws IOException{
        File file = new File(".\\");
        File[] files = file.listFiles();
        String pattern = "seat_table*[0-9]\\.txt";

        if (files != null) {
            for (File f : files) {
                if (f.getName().matches(pattern)) {
                    BufferedReader fileInput = new BufferedReader(new FileReader(f.getName()));
                    BufferedWriter consoleOutput = new BufferedWriter(new OutputStreamWriter(System.out));

                    String line;
                    System.out.println("----------************" + f.getName() + "***********----------");
                    while ((line = fileInput.readLine()) != null) {
                        consoleOutput.write(line);
                        consoleOutput.newLine();
                        consoleOutput.flush();
                    }
                }
            }
        }
    }

    private static void saveTable(String[] tableList) throws IOException {
        int index = 1;
        for (String table : tableList) {
            System.out.println("保存第" + index + "个文件");
            FileOutputStream fileOutputStream = new FileOutputStream(".\\seat_table"+ index +".txt");
            fileOutputStream.write(table.getBytes(StandardCharsets.UTF_8));
            fileOutputStream.flush();
            fileOutputStream.close();
            index ++;
        }
        System.out.println("保存成功");
    }

    private static void saveTable(String[] tableList, TreeSet<Integer> saveIndex) throws IOException {
        int index = 1;
        for (Integer integer : saveIndex) {
            System.out.println("保存第" + index + "个文件");
            FileOutputStream fileOutputStream = new FileOutputStream(".\\seat_table"+ index +".txt");
            fileOutputStream.write(tableList[integer - 1].getBytes(StandardCharsets.UTF_8));
            fileOutputStream.flush();
            fileOutputStream.close();
            index ++;
        }
        System.out.println("保存成功");
    }
}
