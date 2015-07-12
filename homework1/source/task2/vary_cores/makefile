
all:
	number=1 ; while [[ $$number -le 16 ]] ; do \
                echo $$number ; \
                sbatch itermmscript_nobase $$number ; \
                ((number = number + 1)) ; \
        done
clean:
	rm -rf a  core*
