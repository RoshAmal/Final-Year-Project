import streamlit as st
import pandas as pd
from keras.models import load_model

data = load_model("model.h5") 

df=pd.read_csv("DDOS1.csv")
features = ['Fwd Pkt Len Std', 'Fwd Pkt Len Mean',
       'Fwd Pkt Len Max', 'Fwd Seg Size Avg', 'Pkt Len Std', 'Flow IAT Std',
       'Bwd Pkt Len Std', 'Bwd Seg Size Avg', 'Pkt Size Avg',
       'Subflow Fwd Byts']
X = df[features]
X[features] = X[features].apply(pd.to_numeric, errors='coerce', axis=1)
X = X.fillna(0)

def show_predict():

    st.title("DDoS Detection")

    ok=st.button("Predict")
    if ok:
        result=data.predict(X)
        if result>0.5:
            prediction="Network Traffic is DDOS"
        else:
            prediction="Network Traffic is Benign"
        st.subheader(prediction)
