all:
	number=1 ; while [[ $$number -le 16 ]] ; do \
                echo $$number ; \
                sbatch itermmscript_vary_cores $$number ; \
                ((number = number + 1)) ; \
        done
clean:
	rm -rf a  core*
