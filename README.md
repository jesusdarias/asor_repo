# ExplainerLibraries

### How to add a new explainer to the catalog

**1)**	In order to add a new explainer, you have to create a new Resource. First, go to the resources folder and select the folder corresponding to the data type of the explainer you want to add (If your explainer works with a different data type, please add the corresponding folder to the resources folder). For illustration purposes, we will add a new explainer, LIME tabular.

**2)**	Inside the appropriate folder, *create a new .py file* with the name of your explainer. In our case, inside /resources/tabular/ we create the lime.py file.

**3)**	Create a class for the explainer that represents a resource. This class needs to have *two different methods: post and get*. In our example:

```python
from flask_restful import Resource

class Lime(Resource):

	def post(self):
		return {}
		
	def get(self):
		return {}
```
**4)**	In the **post method**, define the mandatory arguments that must be passed for the explainer to get an explanation. In most explainers, this includes the files for the model and data (when needed), and an additional argument called params, which is a dictionary containing parameters such as a particular instance for local methods, configuration options, and additional information needed by the explainer. Note in the example that after parsing the arguments, we use joblib to load the file parameters since the model and data are passed as pickled files.

```python	
class Lime(Resource):

def post(self):
        parser = reqparse.RequestParser()
        parser.add_argument("model", type=werkzeug.datastructures.FileStorage, location='files')
        parser.add_argument("data", type=werkzeug.datastructures.FileStorage, location='files')
        parser.add_argument('params')
        args = parser.parse_args()
        
        data = args.get("data")
        model = args.get("model")
        dataframe = joblib.load(data)
        params_json = json.loads(args.get("params"))
        instance=params_json["instance"]
        backend = params_json["backend"]

	...
```
**5)** Add the actual code for the generation of the explanation to the poste method. **Note:** currently we return a json containing the values of each explanation. This json will also contain a URL to download a plot or image of the explanation when applicable.

**6)** For the get method, we directly return a dictionary that serves a documentation for the explainer. In our example, we include a brief description of the explainer method, the format of the model and data files, and the actual parameters that should be passed in the *params* dictionary. We also include a usage example of this parameters.

```python
def get(self):
        return {
        "_method_description": "LIME perturbs the input data samples in order to train a simple model that approximates the prediction for the given instance and similar ones. "
                           "The explanation contains the weight of each attribute to the prediction value. Requires 3 arguments: " 
                           "the 'params' string, the 'model' which is a file containing the trained model, and " 
                           "the 'data', containing the training data used for the model. These arguments are described below.",

        "model": "The trained prediction model given as a file. The extension must match the backend being used i.e.  a .pkl " 
        "file for Scikit-learn (use Joblib library), .pt for PyTorch or .h5 for TensorFlow models.",

        "data": "Pandas DataFrame containing the training data given as a .pkl file (use Joblib library). The target class must be the last column of the DataFrame",

        "params": { 
                "instance": "Array representing a row with the feature values of an instance not including the target class.",
                "backend": "A string containing the backend of the prediction model. The supported values are: 'sklearn' (Scikit-learn), 'TF1' "
                "(TensorFlow 1.0), 'TF2' (TensorFlow 2.0), 'PYT' (PyTorch).",
                "training_labels": "(Optional) Array of ints representing labels for training data.",
                "feature_names": "(Optional) Array of strings corresponding to the columns in the training data. ", #MIGH DELETE IN FUTURE VERSIONS
                "categorical_features": "(Optional) Array of ints representing the indexes of the categorical columns. Columns not included here will be considered continuous.",
                "class_names": "(Optional) Array of strings containing the names of the possible classes.",
                "output_classes" : "(Optional) Array of ints representing the classes to be explained.",
                "top_classes": "(Optional) Int representing the number of classes with the highest prediction probablity to be explained.",
                "num_features": "(Optional) Int representing the maximum number of features to be included in the explanation."
                },

        "params_example":{
                "backend": "sklearn",
                "instance": [1966, 62, 8, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
                "feature_names": ["construction_year", "surface","floor","no_rooms","district_Bemowo",
                                    "district_Bielany","district_Mokotow","district_Ochota","district_Praga",
                                    "district_Srodmiescie","district_Ursus","district_Ursus","district_Ursynow",
                                    "district_Wola","district_Zoliborz"],
                "categorical_features": [4,5,6,7,8,9,10,11,12,13,14],
                "class_names": ["Cheap", "Expensive"],
                "num_features": 6,
    
               }
        }
```
