import subprocess,tempfile,unittest
from pathlib import Path
BIN=Path(__file__).resolve().parents[1]/'random-number'
class Game(unittest.TestCase):
 def run_game(self,text,cwd):return subprocess.run([str(BIN),'--test-answer','50'],input=text,text=True,capture_output=True,cwd=cwd,timeout=5)
 def test_scores(self):
  with tempfile.TemporaryDirectory() as d:
   self.assertIn('correct number in 1 attempt.',self.run_game('1\n50\nn\n',d).stdout)
   self.assertIn('between 40 and 60',self.run_game('3\n40\ny\n50\nn\n',d).stdout)
   self.assertEqual(Path(d,'highscore.txt').read_text().split(),['1','2147483647','2'])
 def test_loss(self):
  with tempfile.TemporaryDirectory() as d:
   r=self.run_game('3\n10\nn\n90\nn\n20\nn\n',d);self.assertIn('greater than 10',r.stdout);self.assertIn('less than 90',r.stdout);self.assertIn('Game over! The correct number was 50.',r.stdout)
 def test_invalid(self):
  with tempfile.TemporaryDirectory() as d:
   r=self.run_game('x\n1junk\n4\n1\n0\n101\n99999999999999999999\n50oops\n50\nn\n',d);self.assertIn('correct number in 1 attempt.',r.stdout);self.assertEqual(r.stdout.count('Invalid input!'),7)
 def test_eof(self):
  with tempfile.TemporaryDirectory() as d:self.assertEqual(self.run_game('',d).returncode,0);self.assertEqual(self.run_game('1\n',d).returncode,0)
if __name__=='__main__':unittest.main()
