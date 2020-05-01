import Data.List
import Data.Maybe

data Contract = Contract Level Denomination deriving (Eq, Ord)
instance Show Contract where show (Contract level denomination) = show level ++ show denomination
data Denomination = C | D | H | S | X deriving (Show, Read, Eq, Ord, Enum, Bounded)
type Level = Int

main :: IO ()
main = do
  contents <- readFile "Library.asc"
  mapM_ (print . best) $ lines contents

best :: String -> Contract
best xs = bestContract $ filter (> (maximum $ readContractEW xs)) $ makeableContracts $ readContractNS xs

bestContract :: [Contract] -> Contract
bestContract xs = maybe (Contract 0 X) snd (listToMaybe $ sort $ map score xs)

score :: Contract -> (Int, Contract)
score contract@(Contract level denomination)
  | level == 7 = (-(trickScore + 1300), contract)
  | level == 6 = (-(trickScore + 800), contract)
  | trickScore >= 100 = (-(trickScore + 300), contract)
  | level <= 0 = (0, contract)
  | otherwise = (-(trickScore + 50), contract)
  where
    trickScore = trickPoint denomination * level + bonusNT denomination
    trickPoint X = 30
    trickPoint S = 30
    trickPoint H = 30
    trickPoint _ = 20
    bonusNT X = 10
    bonusNT _ = 0

readContractNS :: String -> [Contract]
readContractNS xs = [Contract (hexToInt (xs !! bytes denomination) - 6) denomination | denomination <- [C .. ]]
  where
    bytes x = 85 - 4 * fromEnum x

readContractEW :: String -> [Contract]
readContractEW xs = [Contract (7 - hexToInt (xs !! bytes denomination)) denomination | denomination <- [C .. ]]
  where
    bytes x = 84 - 4 * fromEnum x

makeableContracts :: [Contract] -> [Contract]
makeableContracts = concat . map makeableContractsDenomination
  where
    makeableContractsDenomination :: Contract -> [Contract]
    makeableContractsDenomination (Contract level denomination) = [Contract levels denomination | levels <- [1 .. level]]

hexToInt :: Char -> Int
hexToInt 'A' = 10
hexToInt 'B' = 11
hexToInt 'C' = 12
hexToInt 'D' = 13
hexToInt x = fromEnum x - fromEnum '0'
