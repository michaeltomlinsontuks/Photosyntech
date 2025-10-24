CXX = g++
CXXFLAGS = -std=c++11 -g --coverage -I. -Ithird_party/doctest

DOCTEST_DIR = third_party/doctest
DOCTEST_HEADER = $(DOCTEST_DIR)/doctest.h

.PHONY: fetch-doctest
fetch-doctest:
	@mkdir -p $(DOCTEST_DIR)
	@if [ ! -f $(DOCTEST_HEADER) ]; then \
		echo "Downloading doctest single header..."; \
		curl -sSL -o $(DOCTEST_HEADER) https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h; \
		if [ $$? -ne 0 ]; then \
			echo "Failed to download doctest.h; please download it manually to $(DOCTEST_HEADER)"; exit 1; \
		fi; \
	fi



TEST_SRC = unitTests.cpp\
            strategy/LowWater.cpp\
            strategy/MidWater.cpp\
            strategy/HighWater.cpp\
            strategy/AlternatingWater.cpp\
            strategy/LowSun.cpp\
            strategy/MidSun.cpp\
            strategy/HighSun.cpp\
            singleton/Singleton.cpp\
            prototype/LivingPlant.cpp\
            composite/PlantComponent.cpp\
            state/Dead.cpp\
            state/Mature.cpp\
            state/Seed.cpp\
            state/Vegetative.cpp\
            decorator/PlantAttributes.cpp\
            decorator/ConcreteDecorators.cpp\
			strategy/AlternatingSun.cpp\
			composite/PlantGroup.cpp\
			builder/Director.cpp\
			builder/RoseBuilder.cpp\
			builder/CactusBuilder.cpp\
			iterator/Aggregate.cpp\
			iterator/AggPlant.cpp\
			iterator/AggSeason.cpp\
			iterator/PlantIterator.cpp\
			iterator/SeasonIterator.cpp\
			mediator/Mediator.cpp \
			mediator/Customer.cpp \
			mediator/SalesFloor.cpp \
			mediator/Staff.cpp \
			mediator/SuggestionFloor.cpp\
			observer/Observer.cpp \
			observer/Subject.cpp \
        

SRC = $(TEST_SRC)
OBJ := $(SRC:.cpp=.o)
BIN := app


all: test

test: fetch-doctest
	$(MAKE) SRC="$(TEST_SRC)" all-internal

all-internal: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run r: $(BIN)
	./$(BIN)

test-run: test
	./$(BIN)

cov: test
	./$(BIN)
	gcovr --root . --exclude '.*\.h' --print-summary > coverage.txt
	@echo "Coverage report generated in coverage.txt"

clean c:
	find . -name '*.o' -delete
	rm -f $(BIN) vgcore.*
	find . -name '*.gcno' -delete
	find . -name '*.gcda' -delete
	find . -name '*.gcov' -delete
	rm -f coverage.txt coverage.html coverage.css
	rm -f $(BIN)
	rm  -f $(DEMO_BIN)

valgrind v: $(BIN)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(BIN)

leaks: $(BIN)
	leaks --atExit -- ./$(BIN)

# Demo target for PhotosyntechDemoMain.cpp
DEMO_SRC = PhotosyntechDemoMain.cpp\
            strategy/LowWater.cpp\
            strategy/MidWater.cpp\
            strategy/HighWater.cpp\
            strategy/AlternatingWater.cpp\
            strategy/LowSun.cpp\
            strategy/MidSun.cpp\
            strategy/HighSun.cpp\
            strategy/AlternatingSun.cpp\
            singleton/Singleton.cpp\
            prototype/LivingPlant.cpp\
            composite/PlantComponent.cpp\
            composite/PlantGroup.cpp\
            state/Dead.cpp\
            state/Mature.cpp\
            state/Seed.cpp\
            state/Vegetative.cpp\
            decorator/PlantAttributes.cpp\
            decorator/ConcreteDecorators.cpp\
            builder/Builder.cpp\
            builder/Director.cpp\
            builder/RoseBuilder.cpp\
            builder/SunflowerBuilder.cpp\
            builder/CactusBuilder.cpp\
            builder/PineBuilder.cpp\
            builder/MapleBuilder.cpp\
            builder/JadePlantBuilder.cpp\
            builder/LavenderBuilder.cpp\
            builder/CherryBlossomBuilder.cpp\
            iterator/Aggregate.cpp\
            iterator/AggPlant.cpp\
            iterator/AggSeason.cpp\
            iterator/PlantIterator.cpp\
            iterator/SeasonIterator.cpp\
            mediator/Mediator.cpp\
            mediator/Customer.cpp\
            mediator/SalesFloor.cpp\
            mediator/Staff.cpp\
            mediator/SuggestionFloor.cpp\
            observer/Observer.cpp\
            observer/Subject.cpp

DEMO_OBJ := $(DEMO_SRC:.cpp=.o)
DEMO_BIN := photosyntech_demo

.PHONY: demo demo-run

demo: $(DEMO_BIN)

$(DEMO_BIN): $(DEMO_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

demo-run: demo
	./$(DEMO_BIN)


usageExample_SRC = usageExample.cpp\
            strategy/LowWater.cpp\
            strategy/MidWater.cpp\
            strategy/HighWater.cpp\
            strategy/AlternatingWater.cpp\
            strategy/LowSun.cpp\
            strategy/MidSun.cpp\
            strategy/HighSun.cpp\
            strategy/AlternatingSun.cpp\
            singleton/Singleton.cpp\
            prototype/LivingPlant.cpp\
            composite/PlantComponent.cpp\
            composite/PlantGroup.cpp\
            state/Dead.cpp\
            state/Mature.cpp\
            state/Seed.cpp\
            state/Vegetative.cpp\
            decorator/PlantAttributes.cpp\
            decorator/ConcreteDecorators.cpp\
            builder/Builder.cpp\
            builder/Director.cpp\
            builder/RoseBuilder.cpp\
            builder/SunflowerBuilder.cpp\
            builder/CactusBuilder.cpp\
            builder/PineBuilder.cpp\
            builder/MapleBuilder.cpp\
            builder/JadePlantBuilder.cpp\
            builder/LavenderBuilder.cpp\
            builder/CherryBlossomBuilder.cpp\
            iterator/Aggregate.cpp\
            iterator/AggPlant.cpp\
            iterator/AggSeason.cpp\
            iterator/PlantIterator.cpp\
            iterator/SeasonIterator.cpp\
            mediator/Mediator.cpp\
            mediator/Customer.cpp\
            mediator/SalesFloor.cpp\
            mediator/Staff.cpp\
            mediator/SuggestionFloor.cpp\
            observer/Observer.cpp\
            observer/Subject.cpp

USE_OBJ := $(usageExample_SRC:.cpp=.o)
USE_BIN := usage_app

.PHONY: usage usage-run

usage: $(USE_BIN)

$(USE_BIN): $(USE_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

usage-run ur: usage
	./$(USE_BIN)

valgrind vur: $(USE_BIN)
	valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(USE_BIN)
