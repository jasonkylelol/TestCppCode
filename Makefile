FLAGS = -w -g -fpermissive -std=c++1y -pthread -ldl
CC = g++
SUFFIX = cc

ALLFILES = $(foreach DIR, $(PWD), $(wildcard *.$(SUFFIX)))
SRCS = $(notdir $(ALLFILES))
EXECS = $(patsubst %.$(SUFFIX), %.run, $(SRCS))

.PHONY: clean all
all: $(EXECS)
$(EXECS): %.run: %.$(SUFFIX)
	@echo "======== compile $< ========"
	@$(CC) $(FLAGS) -o $@ $^
clean:
	@rm -f $(PWD)/*.run
	@echo "======== clean done ========"
