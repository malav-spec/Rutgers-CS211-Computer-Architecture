import java.util.*;
class palin
{int num,revnum;
    palin()
    {num=0;
        revnum=0;
    }
    void accept()
    { int n=num;
        
    }
    int reverse(int y)
    {
        if(y>0)
        {
            int x=y%10;
            revnum=revnum+(x*10);
             reverse(y/10);
           
        }
        return revnum;
    }
    void check()
    {if(revnum==num)
        {System.out.println("It is a palindrome number");
            
        }
        else
        System.out.println("Not a palindrome number");
    }
    public static void main()
    {Scanner sc =new Scanner(System.in);
        System.out.println("Enter a number");
        int g=sc.nextInt();
        palin ob=new palin();
        ob.accept();
        
        int z=ob.reverse(g);
        ob.check();
        System.out.println(z);
    }
}