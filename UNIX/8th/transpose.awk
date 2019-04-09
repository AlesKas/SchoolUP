NR==1{	
	n=NF

	for(i=1;i<=NF;i++){
		row[i]=$i
	}
	next
}
{
	if(NF>n){
		n=NF
	}
	for(j=1;j<=NF;j++){
		row[j]=row[j] " " $j
	}
}
END{
	for(k=1;k<=n;k++){
		print row[k]
	}
}
