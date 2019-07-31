import nltk

acceptable_tags = ['NN', 'NNS', 'CD', 'JJ']
file = open("CookbookToGrocery/output.txt", "r")
ingredients = file.readlines()[0].split('|')
cleaned_ingredients = []
for ingred in ingredients:
    tokens = nltk.word_tokenize(ingred)
    tagged_tokens = nltk.pos_tag(tokens)
    filtered = list(filter(lambda x: x[1] in acceptable_tags, tagged_tokens))
    print(filtered)
    cleaned_ingred = ""
    for token in filtered:
        cleaned_ingred = cleaned_ingred + token[0] + " "
    cleaned_ingredients.append(cleaned_ingred)
print(cleaned_ingredients)
