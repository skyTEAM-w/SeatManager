package com.seatmanager.version0;

import java.io.IOException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws IOException {
        SeatManagerImp workSpace = new SeatManagerImp();
        boolean isExit = false;

        while (!isExit) {
            SeatManagerImp.showUI();
            Scanner selectSc = new Scanner(System.in);
            System.out.println("请输入你的选择：");
            switch (selectSc.nextInt()) {
                case 0 -> isExit = true;
                case 1 -> SeatManagerImp.creatTable();
            }
        }
    }
}
