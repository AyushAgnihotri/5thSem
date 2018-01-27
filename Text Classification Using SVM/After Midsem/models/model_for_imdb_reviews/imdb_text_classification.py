import pandas as pd

'''Inputting the Dataset'''
dataset = pd.read_csv('imdb_labelled.tsv', delimiter = '\t', quoting = 3)

dataset.dropna(subset=['Article'], inplace=True)
dataset = dataset.reset_index(drop=True)

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

avg = 0
for i in range(1,101) : 
    '''SVM Classification'''
    from sklearn.cross_validation import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(svdMatrix, y, test_size=0.03, random_state=i)
    
    y_test = [word for word in y_test]
    
    from timeit import default_timer as timer
    from sklearn.svm import SVC
    
    svm = SVC(C=10,kernel='linear')
    svm.fit(X_train, y_train)
    y_pred = svm.predict(X_test)  #Predicted values
    sc = svm.score(X_test, y_test)#Accuracy
    print(sc)
    avg += sc
    
print("average accuracy",avg/100)