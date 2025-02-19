# Definições do compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -g3 -I./include -std=c++17

# Diretórios
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Arquivos fontes e objetos
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
EXEC = $(BINDIR)/sistema_controle_financeiro

# Compilar tudo
all: $(EXEC)

# Gerar executável
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

# Gerar arquivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $(OBJDIR)/$(@F)

# Limpeza
clean:
	rm -f $(OBJDIR)/*.o $(EXEC)

# Rodar o programa
run: $(EXEC)
	@echo "Executando o programa..."
	@./$(EXEC)
