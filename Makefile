-include Makefile.rules
-include var.mk

OBJ_FILES = $(SRC_DIR/*.c:.c=.o)

all: $(LIBRARY_NAME)_lib_static 

$(LIBRARY_NAME)_lib_static: $(OBJ_FILES)
	@echo "Création de la librairie statique"
	@ar rcs $(LIBRARY_NAME).a $(OBJ_FILES)

$(LIBRARY_NAME)_lib_dinamic: $(OBJ_FILES)
	@echo "Création de la librairie dinamique"
	@$(CC) -shared -o $(LIBRARY_NAME).so $(OBJ_FILES) $(LDFLAGS)

compil: $(OBJ_FILES)
	@$(CC) $(CFLAGS) -o programme.out $(OBJ_FILES) $(LDFLAGS)

%.o: %.c
	@$(CC) -c $(CFLAGS) -o $@ $<

check: compil
	@if [ -f option ]; then \
		echo "Exécution de programme.out avec les options du fichier 'option'"; \
		OPTIONS=`cat option`; \
		./programme.out $$OPTIONS; \
	else \
		echo "Fichier 'option' non trouvé."; \
	fi

dev: compil
	@echo "Lancement du mode développement..."
	@tmux new-session -d -s dev_session './programme.out && echo "------------------------------" && echo "Exécution terminée"'
	@while inotifywait -q -r -e modify $(SRC_DIR)/*.c; do \
		if make compil; then \
			echo "Recompilation réussie"; \
			tmux send-keys -t dev_session 'clear && ./programme.out && echo "------------------------------" && echo "Exécution terminée"' Enter; \
		else \
			echo "Erreur de compilation, arrêt."; \
			tmux kill-session -t dev_session; \
			exit 1; \
		fi; \
	done

clang:
	clang-format -i $(SRC_DIR)/*.c

clean:
	@rm -rf $(OBJ_FILES) $(LIBRARY_NAME).a $(LIBRARY_NAME).so programme.out
