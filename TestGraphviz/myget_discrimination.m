function [K]=myget_discrimination(P,S,Es,Et)
%{%Algorithm 15 Compute the perturbed discrimination
%// Compute the Kullback-Leibler number (the discrimination).
%// K: the Kullback-Leibler number.
%// P: the state transition matrix.
%// S: the stimulus matrix.
%// Es: the state visitation vector.
%// Et: the stimulus execution matrix.

%计算NV 特征
n=size(P,1)-1;
Q=P(1:n,1:n);
% Compute the expectation matrix.
N=inv(eye(n,n)-Q);
% Compute the variance matrix. Note that
%diag(N) is a vector, whereas diag(diag(N))
% is a matrix.
V=N*(2*diag(diag(N))-eye(n,n))-(N.*N);


%计算平稳分布
n=size(P,1);
 
%// Get the test case length, plus one.
l=1.0;
for i=1:n-1, l=l+N(1,i); end;
%// Compute the solution.
for i=1:n-1, pi(1,i)=N(1,i)/l; end;
pi(1,n)=1/l;



%// Matrices must be of the same size.
m=size(S,1); n=size(S,2);
%// Compute the log of 2 for use in converting
%// to base two later on.
l2=log(2);
%// This will accumulate the discrimination.
K=0.0;%大k是熵结果。
for i=1:m,
    %// This is the partial sum from the inner summation.
    k=0;%小k是序号
    for j=1:n,
        if S(i,j) > 0,
        %// Normalize the stimulus execution.
            t=Es(i)/Et(i,j);%Et（ij）是从i节点 调用j刺激 的次数。不是状态间的转移次数
            %Es（i）是状态i的在测试时的总次数。 
            k=k+S(i,j)*log(S(i,j)*t)/l2;%先求 公式后半部分
        end;
    end;
    K=K+pi(i)*k;%再结合稳定分布计算全部
end;

end

