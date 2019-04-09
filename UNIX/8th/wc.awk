BEGIN {
	file=ARGV[1]
	ccount = 0
	wcount = 0
	lcount = 0

	while((getline line<file)>0){
		
		split(line, words, " ")
	
		for(i=1;i<=length(words);i++){
			split(words[i], word, "")

			for(j=1;j<=length(word);j++){
				ccount++
			}
			wcount++
		}
		lcount++
	}
	printf "characters: %d\n words: %d\n lines: %d\n", ccount, wcount, lcount
}
