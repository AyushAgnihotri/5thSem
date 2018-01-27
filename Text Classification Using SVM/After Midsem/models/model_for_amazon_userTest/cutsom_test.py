import pandas as pd

'''Inputting the Dataset'''
dataset = pd.read_csv('amazon_cells_labelled.tsv', delimiter = '\t', quoting = 3)

dataset.dropna(subset=['Article'], inplace=True)
dataset = dataset.reset_index(drop=True)
'''asking for user input'''
originalArticles = dataset['Article'].size
countReview = 0
myreviews = []
while(1) :
    print("write a review")
    review = input()
    myreviews.append(review)
    dataset = pd.concat([dataset,pd.DataFrame({'Article':[review],'Category' : ['1'] },index = [originalArticles + countReview])])
    countReview += 1
    print("write more reviews? (yes/no/y/n)")
    choice = input()
    if(choice == 'n' or choice == 'N' or choice == 'no' or choice == 'NO' or choice == 'No' ) :
        break

'''Preparing & Cleaning the Dataset'''
import re
from nltk.corpus import stopwords
from nltk.stem.porter import PorterStemmer
corpus = []
noOfArticles = (dataset['Article'].size)
for i in range(noOfArticles):
	article = re.sub('[^a-zA-Z ]', '', dataset['Article'][i])
	article = article.lower()
	article = article.split()
	ps = PorterStemmer()
	article = [word for word in article if not word in set(stopwords.words('english'))]
	article = [ps.stem(word) for word in article]
	article = ' '.join(article)
	corpus.append(article)

'''Vectorization'''
from sklearn.feature_extraction.text import CountVectorizer
cv = CountVectorizer()
#cv = CountVectorizer(max_features = 21500) #Original = 21911 words
X = cv.fit_transform(corpus).toarray()
y = dataset.iloc[:, 1].values

'''TF-IDF'''
from sklearn.feature_extraction.text import TfidfTransformer
transformer = TfidfTransformer()
tfidf = transformer.fit_transform(X)
tfidf = tfidf.toarray()

'''SVD'''
from sklearn.decomposition import TruncatedSVD
svd = TruncatedSVD(n_components = 75)
svdMatrix = svd.fit_transform(tfidf)
 
'''SVM Classification'''
"""from sklearn.cross_validation import train_test_split
X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.03, random_state=i)

y_test = [word for word in y_test]"""
X_train = svdMatrix[:originalArticles]
X_test = svdMatrix[originalArticles:]
y_train = y[:originalArticles]
y_train = [word for word in y_train]
from sklearn.svm import SVC

svm = SVC(C=10,kernel='linear')
svm.fit(X_train, y_train)
y_pred = svm.predict(X_test)  #Predicted values

for i in range(len(myreviews)) :
    
    print(str(i+1) + ". " + myreviews[i])
    if(y_pred[i] == 0) :
        print("we rated this review as  : Negative") 
    else :
        print("we rated this review as  : Positive")
    
    choice = input("are we correct ?? yes/no  :  ")
    if(choice == 'y' or choice == 'Y' or choice == 'yes' or choice == 'YES' or choice == 'Yes' ) :
        fill = str(y_pred[i])
    else :
        fill = str(1 - y_pred[i])
        
    with open('amazon_cells_labelled.tsv','a') as myfile :
        print(myreviews[i] + "\t" + fill, file = myfile )
