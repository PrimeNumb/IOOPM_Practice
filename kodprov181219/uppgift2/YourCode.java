/*
  NOTE! 
  This is the only file you are allowed to make changes too as it
  is the only file that is handed in by make handin!

  To help you, this file is divided into four parts:

  0. Additions -- a space for adding any new classes needed
  1. Dirty extensions -- classes whose methods you will likely have to change
  2. Clean extensions -- classes that you will likely have to add new methods to
  3. Ignore -- stuff you can likely safely ignore

 */

////////////////////////////////////////////////////////////////////////////////
/// ADDITI0NS //////////////////////////////////////////////////////////////////

class Quote extends Expression
{
    private Expression subExpr;

    public Quote(Expression e)
    {
	this.subExpr = e;
    }

    public Constant eval()
    {
	return new StringLiteral(this.subExpr.asString());
    }

    public String asString()
    {
	return "Quote(" + this.subExpr.asString() + ")";
    }
    
    @Override
    public String toString()
    {
	return "Quote(" + this.subExpr.toString() + ")";
    }
}
class Unquote extends Expression
{
    private Expression subExpr;

    public Unquote(Expression e)
    {	
	this.subExpr = e;
    }

    @Override
    public String toString()
    {
	return "Unquote(" + this.subExpr.toString() + ")";
    }

    public String asString()
    {
	if(this.subExpr instanceof Unquote)
	{
	    throw new RuntimeException("Unquote appeared outside of Quote");
	}
	
	return this.subExpr.eval().asString();
    }

    public Constant eval()
    {
	throw new RuntimeException("Unquote appeared outside of Quote");
    }
}

/// Hint: one possible way to implement Quote/Unquote is to introduce
/// another form of "evaluation" in a method called asString(). If you want to use
/// such a solution -- look at the asString() methods in ASTFixed.java

/// Do not forget to add toString() methods or tests will complain. 

/// If you need the Environement, look at how it is obtained elsewhere.

////////////////////////////////////////////////////////////////////////////////
/// DIRTY EXTENSI0NS ///////////////////////////////////////////////////////////

/// Tobias: probably no need to add anything here!

////////////////////////////////////////////////////////////////////////////////
/// CLEAN EXTENSI0NS ///////////////////////////////////////////////////////////

/// Tobias: probably no need to add anything here!

////////////////////////////////////////////////////////////////////////////////
/// IGN0RE /////////////////////////////////////////////////////////////////////

// Required by Java so we can name the file YourCode.java 
public class YourCode {}

