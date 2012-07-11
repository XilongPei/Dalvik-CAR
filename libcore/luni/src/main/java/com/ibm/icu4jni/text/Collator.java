/**
*******************************************************************************
* Copyright (C) 1996-2005, International Business Machines Corporation and    *
* others. All Rights Reserved.                                                *
*******************************************************************************
*
*
*******************************************************************************
*/

package com.ibm.icu4jni.text;

import java.util.Locale;

public abstract class Collator implements Cloneable {
    /**
     * Strongest collator strength value. Typically used to denote differences
     * between base characters. See class documentation for more explanation.
     * @see #setStrength
     * @see #getStrength
     * @stable ICU 2.4
     */
    public final static int PRIMARY = CollationAttribute.VALUE_PRIMARY;

    /**
     * Second level collator strength value.
     * Accents in the characters are considered secondary differences.
     * Other differences between letters can also be considered secondary
     * differences, depending on the language.
     * See class documentation for more explanation.
     * @see #setStrength
     * @see #getStrength
     * @stable ICU 2.4
     */
    public final static int SECONDARY = CollationAttribute.VALUE_SECONDARY;

    /**
     * Third level collator strength value.
     * Upper and lower case differences in characters are distinguished at this
     * strength level. In addition, a variant of a letter differs from the base
     * form on the tertiary level.
     * See class documentation for more explanation.
     * @see #setStrength
     * @see #getStrength
     * @stable ICU 2.4
     */
    public final static int TERTIARY = CollationAttribute.VALUE_TERTIARY;

    /**
     * Fourth level collator strength value.
     * When punctuation is ignored
     * <a href="http://www-124.ibm.com/icu/userguide/Collate_Concepts.html#Ignoring_Punctuation">
     * (see Ignoring Punctuations in the user guide)</a> at PRIMARY to TERTIARY
     * strength, an additional strength level can
     * be used to distinguish words with and without punctuation.
     * See class documentation for more explanation.
     * @see #setStrength
     * @see #getStrength
     * @stable ICU 2.4
     */
    public final static int QUATERNARY = CollationAttribute.VALUE_QUATERNARY;

    /**
     * <p>
     * Smallest Collator strength value. When all other strengths are equal,
     * the IDENTICAL strength is used as a tiebreaker. The Unicode code point
     * values of the NFD form of each string are compared, just in case there
     * is no difference.
     * See class documentation for more explanation.
     * </p>
     * <p>
     * Note this value is different from JDK's
     * </p>
     * @stable ICU 2.4
     */
    public final static int IDENTICAL = CollationAttribute.VALUE_IDENTICAL;

    /**
     * <p>Decomposition mode value. With NO_DECOMPOSITION set, Strings
     * will not be decomposed for collation. This is the default
     * decomposition setting unless otherwise specified by the locale
     * used to create the Collator.</p>
     *
     * <p><strong>Note</strong> this value is different from the JDK's.</p>
     * @see #CANONICAL_DECOMPOSITION
     * @see #getDecomposition
     * @see #setDecomposition
     * @stable ICU 2.4
     */
    public final static int NO_DECOMPOSITION = CollationAttribute.VALUE_OFF;

    /**
     * <p>Decomposition mode value. With CANONICAL_DECOMPOSITION set,
     * characters that are canonical variants according to the Unicode standard
     * will be decomposed for collation.</p>
     *
     * <p>CANONICAL_DECOMPOSITION corresponds to Normalization Form D as
     * described in <a href="http://www.unicode.org/unicode/reports/tr15/">
     * Unicode Technical Report #15</a>.
     * </p>
     * @see #NO_DECOMPOSITION
     * @see #getDecomposition
     * @see #setDecomposition
     * @stable ICU 2.4
     */
    public final static int CANONICAL_DECOMPOSITION = CollationAttribute.VALUE_ON;

    public static Collator getInstance(Locale locale) {
        return new RuleBasedCollator(locale);
    }

    public boolean equals(String source, String target) {
        return (compare(source, target) == 0);
    }

    public abstract boolean equals(Object target);

    public abstract Object clone() throws CloneNotSupportedException;

    /**
     * The comparison function compares the character data stored in two
     * different strings. Returns information about whether a string is less
     * than, greater than or equal to another string.
     * <p>Example of use:
     * <pre>
     * .  Collator myCollation = Collator.getInstance(Locale::US);
     * .  myCollation.setStrength(CollationAttribute.VALUE_PRIMARY);
     * .  // result would be CollationAttribute.VALUE_EQUAL
     * .  // ("abc" == "ABC")
     * .  // (no primary difference between "abc" and "ABC")
     * .  int result = myCollation.compare("abc", "ABC",3);
     * .  myCollation.setStrength(CollationAttribute.VALUE_TERTIARY);
     * .  // result would be Collation.LESS (abc" &lt;&lt;&lt; "ABC")
     * .  // (with tertiary difference between "abc" and "ABC")
     * .  int result = myCollation.compare("abc", "ABC",3);
     * </pre>
     * @stable ICU 2.4
     */
    public abstract int compare(String source, String target);

    /**
     * Get the decomposition mode of this Collator.
     * @return the decomposition mode
     * @see #CANONICAL_DECOMPOSITION
     * @see #NO_DECOMPOSITION
     * @stable ICU 2.4
     */
    public abstract int getDecomposition();

    /**
     * Set the normalization mode used int this object
     * The normalization mode influences how strings are compared.
     * @param mode desired normalization mode
     * @see #CANONICAL_DECOMPOSITION
     * @see #NO_DECOMPOSITION
     * @stable ICU 2.4
     */
    public abstract void setDecomposition(int mode);

    /**
     * Determines the minimum strength that will be use in comparison or
     * transformation.
     * <p>
     * E.g. with strength == SECONDARY, the tertiary difference is ignored
     * </p>
     * <p>
     * E.g. with strength == PRIMARY, the secondary and tertiary difference
     * are ignored.
     * </p>
     * @return the current comparison level.
     * @see #PRIMARY
     * @see #SECONDARY
     * @see #TERTIARY
     * @see #QUATERNARY
     * @see #IDENTICAL
     * @stable ICU 2.4
     */
    public abstract int getStrength();

    /**
     * Gets the attribute to be used in comparison or transformation.
     * @param type the attribute to be set from CollationAttribute
     * @return value attribute value from CollationAttribute
     * @stable ICU 2.4
     */
    public abstract int getAttribute(int type);

    /**
     * Sets the minimum strength to be used in comparison or transformation.
     * <p>Example of use:
     * <pre>
     * . Collator myCollation = Collator.createInstance(Locale::US);
     * . myCollation.setStrength(PRIMARY);
     * . // result will be "abc" == "ABC"
     * . // tertiary differences will be ignored
     * . int result = myCollation->compare("abc", "ABC");
     * </pre>
     * @param strength the new comparison level.
     * @see #PRIMARY
     * @see #SECONDARY
     * @see #TERTIARY
     * @see #QUATERNARY
     * @see #IDENTICAL
     * @stable ICU 2.4
     */
     public abstract void setStrength(int strength);

    /**
     * Sets the attribute to be used in comparison or transformation.
     * <p>Example of use:
     * <pre>
     * . Collator myCollation = Collator.createInstance(Locale::US);
     * . myCollation.setAttribute(CollationAttribute.CASE_LEVEL,
     * .                          CollationAttribute.VALUE_ON);
     * . int result = myCollation->compare("\\u30C3\\u30CF",
     * .                                   "\\u30C4\\u30CF");
     * . // result will be -1.
     * </pre>
     * @param type the attribute to be set from CollationAttribute
     * @param value attribute value from CollationAttribute
     * @stable ICU 2.4
     */
    public abstract void setAttribute(int type, int value);

    /**
     * Get the sort key as an CollationKey object from the argument string.
     * To retrieve sort key in terms of byte arrays, use the method as below<br>
     * <code>
     * Collator collator = Collator.getInstance();
     * CollationKey collationKey = collator.getCollationKey("string");
     * byte[] array = collationKey.toByteArray();
     * </code><br>
     * Byte array result are zero-terminated and can be compared using
     * java.util.Arrays.equals();
     * @param source string to be processed.
     * @return the sort key
     * @stable ICU 2.4
     */
    public abstract CollationKey getCollationKey(String source);

    /**
     * Returns a hash of this collation object
     * @return hash of this collation object
     * @stable ICU 2.4
     */
    public abstract int hashCode();
}
