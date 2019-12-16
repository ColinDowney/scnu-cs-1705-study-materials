function [B]=deZigzagScan(A,x,y)
m=min(x,y);
n=max(x,y);
B=zeros(m,n);
sum=1;
f=0;
index=1;
if x>y
index=2;
end
for i=1:m+n-1
 sum=sum+f;
 if i<=m
   f=i;
 if mod(index,2)==0
   B=B+[rot90(diag(A(1,sum:sum+f-1),i-m),-45)',zeros(m,n-m)];
 else
 B=B+[rot90(diag(A(1,sum:sum+f-1),i-m),-45),zeros(m,n-m)];
 end
 else if i<=n
 f=m;
 if mod(index,2)==0
 B=B+[zeros(m,i-m),rot90(diag(A(1,sum:sum+f-1)),-45)',zeros(m,n-i)];
 else
 B=B+[zeros(m,i-m),rot90(diag(A(1,sum:sum+f-1)),-45),zeros(m,n-i)];
 end
     else
 f=m+n-i;
 if mod(index,2)==0
 B=B+[zeros(m,n-m),rot90(diag(A(1,sum:sum+f-1),i-n),-45)'];
 else
 B=B+[zeros(m,n-m),rot90(diag(A(1,sum:sum+f-1),i-n),-45)];
 end
     end
 end
 index=index+1;
end
if x>y
 B=B';
end
end


