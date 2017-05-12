
class
    RECTANGLE

inherit
    ARGUMENTS
    DOUBLE_MATH

create
    make
feature
            x1: DOUBLE
            y1: DOUBLE
            x2: DOUBLE
            y2: DOUBLE
            x3: DOUBLE
            y3: DOUBLE
            x4: DOUBLE
            y4: DOUBLE
            p:  DOUBLE
            temp1: DOUBLE
            temp2: DOUBLE
feature
    make
        do
            -- Add your code here
            print ("Hellorld!%N")
            x1:=0
            y1:=0
            x2:=0
            y2:=1
            x3:=2
            y3:=1
            x4:=2
            y4:=0
        end

feature

    translate_x(a: DOUBLE)
       
        require
            
        do
            x1:=x1+a
            x2:=x2+a
            x3:=x3+a
            x4:=x4+a
        end
    translate_y(a: DOUBLE)
        require
            
        do
            y1:=y1+a
            y2:=y2+a
            y3:=y3+a
            y4:=y4+a
        ensure
            
        end
    scaling (a: DOUBLE)
        require
            
        do
            p:=a
      	    x2:=p*x2-(p-1)*x1
      	    y2:=p*y2-(p-1)*x1
      	    x3:=x2+x4-x1
      	    y3:=y2+y4-y1
      	    x4:=p*x4-(p-1)*x1
      	    y4:=p*y4-(p-1)*y1
        ensure
            
        end
    rotate (a: DOUBLE)
        require
            
        do

        ensure
            
        end
end

